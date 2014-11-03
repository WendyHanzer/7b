#include "lighting.hpp"
#include "engine.hpp"

#include <iostream>

LightingProgram::LightingProgram()
{
    init();
}

LightingProgram::~LightingProgram()
{

}

void LightingProgram::init()
{
    loadShaders();
    initProgram();
    initLocations();
}

void LightingProgram::bind()
{
    glUseProgram(program);
}

void LightingProgram::unbind()
{
    glUseProgram(0);
}

void LightingProgram::loadShaders()
{
    shaders[0] = Program::loadShader("../shaders/lighting.vs", GL_VERTEX_SHADER);
    shaders[1] = Program::loadShader("../shaders/lighting.fs", GL_FRAGMENT_SHADER);
}

void LightingProgram::initProgram()
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
        glGetShaderInfoLog(program, 512, NULL, buffer); // inserts the error into the buffer
        std::cerr << buffer << std::endl;

        exit(1);
    }

    if(Engine::getEngine()->getOptions().verbose)
        std::cout << "Created GL Program: LightingProgram " << program << std::endl;
}

void LightingProgram::initLocations()
{
    locations["vs_pos"] = glGetAttribLocation(program, "vs_pos");
    locations["vs_norm"] = glGetAttribLocation(program, "vs_norm");
    locations["vs_uv"] = glGetAttribLocation(program, "vs_uv");

    locations["mvp"] = glGetUniformLocation(program, "mvp");
    locations["light_dir"] = glGetUniformLocation(program, "light_dir");
    locations["cameraPos"] = glGetUniformLocation(program, "cameraPos");
    locations["specularIntensity"] = glGetUniformLocation(program, "specularIntensity");
    locations["specularPower"] = glGetUniformLocation(program, "specularPower");
    locations["ambientIntensity"] = glGetUniformLocation(program, "ambientIntensity");
    locations["tex"] = glGetUniformLocation(program, "tex");
}