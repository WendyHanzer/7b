#include "engine.hpp"
#include "graphics.hpp"
#include "vertex.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "texture.hpp"
#include "lighting.hpp"
#include "cube.hpp"
#include "shadowmap.hpp"

#include "gl.hpp"

#include <FreeImagePlus.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <fstream>
#include <iostream>
#include <utility>

Graphics::Graphics(Engine *eng)
    : engine(eng)
{
    camera = new Camera(engine);
}

Graphics::~Graphics()
{
    if(camera)
        delete camera;
}

void Graphics::init()
{
    #ifdef __APPLE__
    int windowWidth = 1024, windowHeight = 768;
    #else
    int windowWidth = 1600, windowHeight = 900;
    #endif

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow("CS791a", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if(!window) {
        std::cerr << "Unable to create SDL Window" << std::endl;
        exit(1);
    }

    gl_context = SDL_GL_CreateContext(window);

    SDL_GL_SetSwapInterval(1);

    initGL();
    initScenes();
}

void Graphics::initGL()
{
    #ifndef __APPLE__
    glewExperimental = GL_TRUE;
    GLenum status = glewInit();
    if(status != GLEW_OK) {
        std::cerr << "Unable to initialize glew" << std::endl;
        exit(1);
    }
    #endif

    if(engine->getOptions().verbose)
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(0.0, 0.0, 0.0, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //glEnable(GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

    //glShadeModel (GL_FLAT);

    //glEnable(GL_MULTISAMPLE_ARB);

    if(engine->getOptions().wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe

    updateView();
    windowResized();

    programs["lighting"] = new LightingProgram();
}

void Graphics::tick(float dt)
{
    //cube->tick(dt);
    scene->tick(dt);
    render();
}

void Graphics::render()
{
    updateCamera();
    updateView();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->render();
    //cube->render();

    SDL_GL_SwapWindow(window);
}

void Graphics::stop()
{
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
}

void Graphics::updateView()
{
    view = camera->getView();
}

void Graphics::updateCamera()
{
    camera->update();
}

void Graphics::windowResized()
{
    int width, height;
    getWindowSize(width, height);
    glViewport(0, 0, width, height);
    projection = glm::perspective(45.0f, float(width) / float(height),
                                        0.01f, 1000000.0f);
}

void Graphics::getWindowSize(int &w, int &h) const
{
    SDL_GetWindowSize(window, &w, &h);
}

Program* Graphics::getShaderProgram(const std::string& name) const
{
    return programs.at(name);
}

void Graphics::setClearColor(const glm::vec3& color){
    glClearColor(color[0], color[1], color[2], 1.0f);
}

void Graphics::initScenes()
{
    //cube = new Cube();
    scene = new ShadowMapScene();
    scene->init();
}
