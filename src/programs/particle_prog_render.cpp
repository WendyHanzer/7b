#include "particle_prog_render.hpp"
#include "lighting.hpp"
#include "engine.hpp"

#include <iostream>

ParticleRenderProgram::ParticleRenderProgram()
{
    init();
}

ParticleRenderProgram::~ParticleRenderProgram()
{

}

void ParticleRenderProgram::init()
{
    loadShaders();
    initProgram();
    initLocations();
}

void ParticleRenderProgram::bind()
{
    glUseProgram(program);
}

void ParticleRenderProgram::unbind()
{
    glUseProgram(0);
}

void ParticleRenderProgram::loadShaders()
{
    shaders[0] = Program::loadShader("../shaders/particles_render.vs", GL_VERTEX_SHADER);
    shaders[1] = Program::loadShader("../shaders/particles_render.fs", GL_FRAGMENT_SHADER);
    shaders[2] = Program::loadShader("../shaders/particles_render.gs", GL_GEOMETRY_SHADER);
}

void ParticleRenderProgram::initProgram()
{
    program = glCreateProgram();
    glAttachShader(program, shaders[0]);
    glAttachShader(program, shaders[1]);
    glAttachShader(program, shaders[2]);

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
        std::cout << "Created GL Program: ParticleRenderProgram " << program << std::endl;
}

void ParticleRenderProgram::initLocations()
{
    locations["vp"] = glGetUniformLocation(program, "vp");
    locations["camera_pos"] = glGetUniformLocation(program, "camera_pos");
    locations["color_map"] = glGetUniformLocation(program, "color_map");
    locations["billboard_size"] = glGetUniformLocation(program, "billboard_size");

    for(const auto& pair : locations) {
        if(pair.second < 0)
            std::cout << "Program: Render  Unable to find location: " << pair.first << std::endl;
    }
}