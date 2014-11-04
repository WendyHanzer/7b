#include "plane.hpp"
#include "texture.hpp"
#include "engine.hpp"
#include "graphics.hpp"
#include "programs/lighting.hpp"
#include "gl.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/texture.h>

Plane::Plane(int width, int height)
{
    init();
}

Plane::~Plane()
{

}

void Plane::init()
{
    program = Engine::getEngine()->graphics->getShaderProgram("lighting");
    texture = new Texture("../assets/reflection.jpg", GL_TEXTURE_2D);

    geometry = {
    {{-1.0f,-1.0f,-1.0f}}, // triangle 1 : begin
    {{-1.0f,-1.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}}, // triangle 1 : end
    {{1.0f, 1.0f,-1.0f}}, // triangle 2 : begin
    {{-1.0f,-1.0f,-1.0f}},
    {{-1.0f, 1.0f,-1.0f}}, // triangle 2 : end
    {{1.0f,-1.0f, 1.0f}},
    {{-1.0f,-1.0f,-1.0f}},
    {{1.0f,-1.0f,-1.0f}},
    {{1.0f, 1.0f,-1.0f}},
    {{1.0f,-1.0f,-1.0f}},
    {{-1.0f,-1.0f,-1.0f}},
    {{-1.0f,-1.0f,-1.0f}},
    {{-1.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f,-1.0f}},
    {{1.0f,-1.0f, 1.0f}},
    {{-1.0f,-1.0f, 1.0f}},
    {{-1.0f,-1.0f,-1.0f}},
    {{-1.0f, 1.0f, 1.0f}},
    {{-1.0f,-1.0f, 1.0f}},
    {{1.0f,-1.0f, 1.0f}},
    {{1.0f, 1.0f, 1.0f}},
    {{1.0f,-1.0f,-1.0f}},
    {{1.0f, 1.0f,-1.0f}},
    {{1.0f,-1.0f,-1.0f}},
    {{1.0f, 1.0f, 1.0f}},
    {{1.0f,-1.0f, 1.0f}},
    {{1.0f, 1.0f, 1.0f}},
    {{1.0f, 1.0f,-1.0f}},
    {{-1.0f, 1.0f,-1.0f}},
    {{1.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f,-1.0f}},
    {{-1.0f, 1.0f, 1.0f}},
    {{1.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}},
    {{1.0f,-1.0f, 1.0f}}
};

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * geometry.size(), geometry.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(program->getLocation("vs_pos"),
                            3,
                            GL_FLOAT,
                            GL_FALSE,
                            sizeof(Vertex),
                            (void*)offsetof(Vertex,pos));
}

void Plane::tick(float dt)
{
    //model = glm::rotate(model, 10.0f * dt, glm::vec3(0,1,0));
}

void Plane::render()
{
    glm::mat4 mvp = Engine::getEngine()->graphics->projection * Engine::getEngine()->graphics->view * model;
    program->bind();
    program->set("mvp", mvp);
    program->set("ambientIntensity", 1.0f);
    program->set("tex", 0);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);

    texture->bind(GL_TEXTURE0);

    glDrawArrays(GL_TRIANGLES, 0, geometry.size());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    program->unbind();
}

void Plane::scale(float scaleValue)
{
    model = glm::scale(model, glm::vec3(scaleValue,scaleValue,scaleValue));
}
