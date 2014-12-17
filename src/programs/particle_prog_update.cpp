#include "particle_prog_update.hpp"
#include "lighting.hpp"
#include "engine.hpp"

#include <iostream>

ParticleUpdateProgram::ParticleUpdateProgram()
{
    init();
}

ParticleUpdateProgram::~ParticleUpdateProgram()
{

}

void ParticleUpdateProgram::init()
{
    loadShaders();
    initProgram();
    initLocations();
}

void ParticleUpdateProgram::bind()
{
    glUseProgram(program);
}

void ParticleUpdateProgram::unbind()
{
    glUseProgram(0);
}

void ParticleUpdateProgram::loadShaders()
{
    shaders[0] = Program::loadShader("../shaders/particles_update.vs", GL_VERTEX_SHADER);
    shaders[1] = Program::loadShader("../shaders/particles_update.fs", GL_FRAGMENT_SHADER);
    shaders[2] = Program::loadShader("../shaders/particles_update.gs", GL_GEOMETRY_SHADER);
}

void ParticleUpdateProgram::initProgram()
{
    program = glCreateProgram();
    glAttachShader(program, shaders[0]);
    glAttachShader(program, shaders[1]);
    glAttachShader(program, shaders[2]);


    const GLchar* varyings[4];
    varyings[0] = "Type1";
    varyings[1] = "Position1";
    varyings[2] = "Velocity1";
    varyings[3] = "Age1";

    glTransformFeedbackVaryings(program, 4, varyings, GL_INTERLEAVED_ATTRIBS);

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
        std::cout << "Created GL Program: ParticleUpdateProgram " << program << std::endl;
}

void ParticleUpdateProgram::initLocations()
{
    // locations["vs_pos"] = glGetAttribLocation(program, "vs_pos");
    // locations["vs_norm"] = glGetAttribLocation(program, "vs_norm");
    // locations["vs_uv"] = glGetAttribLocation(program, "vs_uv");

    // locations["mvp"] = glGetUniformLocation(program, "mvp");
    // locations["modelMatrix"] = glGetUniformLocation(program, "modelMatrix");
    // locations["light_dir"] = glGetUniformLocation(program, "light_dir");
    // locations["cameraPos"] = glGetUniformLocation(program, "cameraPos");
    // locations["specularIntensity"] = glGetUniformLocation(program, "specularIntensity");
    // locations["specularPower"] = glGetUniformLocation(program, "specularPower");
    // locations["ambientIntensity"] = glGetUniformLocation(program, "ambientIntensity");
    // locations["diffuseIntensity"] = glGetUniformLocation(program, "diffuseIntensity");
    // locations["pointLightPos"] = glGetUniformLocation(program, "pointLightPos");
    // locations["spotLightDir"] = glGetUniformLocation(program, "spotLightDir");
    // locations["tex"] = glGetUniformLocation(program, "tex");

    locations["dt"] = glGetUniformLocation(program, "dt");
    locations["random_texture"] = glGetUniformLocation(program, "random_texture");
    locations["time"] = glGetUniformLocation(program, "time");
    locations["launcher_lifetime"] = glGetUniformLocation(program, "launcher_lifetime");
    locations["shell_lifetime"] = glGetUniformLocation(program, "shell_lifetime");
    locations["secondary_shell_lifetime"] = glGetUniformLocation(program, "secondary_shell_lifetime");

    for(const auto& pair : locations) {
        if(pair.second < 0)
            std::cout << "Program: Update  Unable to find location: " << pair.first << std::endl;
    }
}