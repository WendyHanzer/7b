#include "flag.hpp"
#include "engine.hpp"

#include <iostream>

FlagProgram::FlagProgram()
{
    init();
}

FlagProgram::~FlagProgram()
{

}

void FlagProgram::init()
{
    loadShaders();
    initProgram();
    initLocations();
}

void FlagProgram::bind()
{
    glUseProgram(program);
}

void FlagProgram::unbind()
{
    glUseProgram(0);
}

void FlagProgram::loadShaders()
{
    shaders[0] = Program::loadShader("../shaders/flag.vs", GL_VERTEX_SHADER);
    shaders[1] = Program::loadShader("../shaders/flag.fs", GL_FRAGMENT_SHADER);
}

void FlagProgram::initProgram()
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
        std::cout << "Created GL Program: FlagProgram " << program << std::endl;
}

void FlagProgram::initLocations()
{
    locations["vs_pos"] = glGetAttribLocation(program, "vs_pos");
    locations["vs_norm"] = glGetAttribLocation(program, "vs_norm");
    locations["vs_uv"] = glGetAttribLocation(program, "vs_uv");

    locations["mvp"] = glGetUniformLocation(program, "mvp");
    locations["modelMatrix"] = glGetUniformLocation(program, "modelMatrix");
    locations["light_dir"] = glGetUniformLocation(program, "light_dir");
    locations["cameraPos"] = glGetUniformLocation(program, "cameraPos");
    locations["specularIntensity"] = glGetUniformLocation(program, "specularIntensity");
    locations["specularPower"] = glGetUniformLocation(program, "specularPower");
    locations["ambientIntensity"] = glGetUniformLocation(program, "ambientIntensity");
    locations["diffuseIntensity"] = glGetUniformLocation(program, "diffuseIntensity");
    locations["pointLightPos"] = glGetUniformLocation(program, "pointLightPos");
    locations["spotLightDir"] = glGetUniformLocation(program, "spotLightDir");
    locations["tex"] = glGetUniformLocation(program, "tex");

    locations["waveTime"] = glGetUniformLocation(program, "waveTime");
    locations["waveWidth"] = glGetUniformLocation(program, "waveWidth");
    locations["waveHeight"] = glGetUniformLocation(program, "waveHeight");

    for(const auto& pair : locations) {
        if(pair.second < 0)
            std::cout << "Program: Flag  Unable to find location: " << pair.first << std::endl;
    }
}