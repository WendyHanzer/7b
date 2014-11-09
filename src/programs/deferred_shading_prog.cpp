#include "deferred_shading_prog.hpp"
#include "engine.hpp"

#include <iostream>

DeferredShadingProgram::DeferredShadingProgram()
{
    init();
}

DeferredShadingProgram::~DeferredShadingProgram()
{

}

void DeferredShadingProgram::init()
{
    loadShaders();
    initProgram();
    initLocations();
}

void DeferredShadingProgram::bind()
{
    glUseProgram(program);
}

void DeferredShadingProgram::unbind()
{
    glUseProgram(0);
}

void DeferredShadingProgram::loadShaders()
{
    shaders[0] = Program::loadShader("../shaders/deferred_shading.vs", GL_VERTEX_SHADER);
    shaders[1] = Program::loadShader("../shaders/deferred_shading.fs", GL_FRAGMENT_SHADER);
}

void DeferredShadingProgram::initProgram()
{
    program = glCreateProgram();
    glAttachShader(program, shaders[0]);
    glAttachShader(program, shaders[1]);

    glLinkProgram(program);

    GLint shader_status;
    glGetProgramiv(program, GL_LINK_STATUS, &shader_status);
    if(!shader_status) {
        std::cerr << "Unable to create shader program!" << std::endl;

        char buffer[512];
        glGetProgramInfoLog(program, 512, NULL, buffer); // inserts the error into the buffer
        std::cerr << buffer << std::endl;

        exit(1);
    }

    if(Engine::getEngine()->getOptions().verbose)
        std::cout << "Created GL Program: DeferredShadingProgram " << program << std::endl;
}

void DeferredShadingProgram::initLocations()
{
    locations["vs_pos"] = 0;
    locations["vs_uv"] = 1;
    locations["vs_norm"] = 2;

    locations["mvp"] = glGetUniformLocation(program, "mvp");
    locations["modelMatrix"] = glGetUniformLocation(program, "modelMatrix");
    locations["colorMap"] = glGetUniformLocation(program, "colorMap");
}