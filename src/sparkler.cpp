#include "sparkler.hpp"
#include "engine.hpp"
#include "graphics.hpp"
#include "vertex.hpp"

Sparkler::Sparkler(Engine *eng)
    : engine(eng)
{
    maxParticles = engine->getOptions().max_particles;
    numParticles = 0;
    init();
}

Sparkler::~Sparkler()
{

}

void Sparkler::init()
{
    initGL();
}

void Sparkler::initGL()
{
    const GLfloat g_vertex_buffer_data[] = {
     -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     -0.5f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f,
    };

    program = engine->graphics->getShaderProgram("sparkler");

    glGenVertexArrays(1, &vao_main);
    glBindVertexArray(vao_main);

    glGenBuffers(1, &vbo_main);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_main);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao_pos);
    glBindVertexArray(vao_pos);

    glGenBuffers(1, &vbo_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    glBufferData(GL_ARRAY_BUFFER, numParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

    glGenVertexArrays(1, &vao_color);
    glBindVertexArray(vao_color);

    glGenBuffers(1, &vbo_color);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
    glBufferData(GL_ARRAY_BUFFER, numParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);


}

void Sparkler::tick(float dt)
{

}

void Sparkler::render()
{
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(vao_main);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_main);
    glVertexAttribPointer(
     0, // attribute. No particular reason for 0, but must match the layout in the shader.
     3, // size
     GL_FLOAT, // type
     GL_FALSE, // normalized?
     0, // stride
     (void*)0 // array buffer offset
    );

    // 2nd attribute buffer : positions of particles' centers
    glEnableVertexAttribArray(vao_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    glVertexAttribPointer(
     1, // attribute. No particular reason for 1, but must match the layout in the shader.
     4, // size : x + y + z + size => 4
     GL_FLOAT, // type
     GL_FALSE, // normalized?
     0, // stride
     (void*)0 // array buffer offset
    );

    // 3rd attribute buffer : particles' colors
    glEnableVertexAttribArray(vao_color);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
    glVertexAttribPointer(
     2, // attribute. No particular reason for 1, but must match the layout in the shader.
     4, // size : r + g + b + a => 4
     GL_UNSIGNED_BYTE, // type
     GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
     0, // stride
     (void*)0 // array buffer offset
    );

    glVertexAttribDivisor(0,0);
    glVertexAttribDivisor(1,1);
    glVertexAttribDivisor(2,1);

    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, numParticles);
}
