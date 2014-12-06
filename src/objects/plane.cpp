#include "plane.hpp"
#include "texture.hpp"
#include "engine.hpp"
#include "graphics.hpp"
#include "programs/lighting.hpp"
#include "gl.hpp"
#include "mesh.hpp"

#include <glm/gtc/matrix_transform.hpp>

Plane::Plane(Program *prog, int width, int height)
{
    program = prog;
    init();
}

Plane::~Plane()
{

}

void Plane::init()
{
    texture = new Texture("../assets/reflection.jpg", GL_TEXTURE_2D);

    geometry = Mesh::load("../assets/objects/plane.ply");

    for(auto& vertex : geometry) {
        vertex.texture[0] = vertex.pos[0] / 10.0f;
        vertex.texture[1] = vertex.pos[2] / 10.0f;
    }

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

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(program->getLocation("vs_norm"),
                            3,
                            GL_FLOAT,
                            GL_FALSE,
                            sizeof(Vertex),
                            (void*)offsetof(Vertex,normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(program->getLocation("vs_uv"),
                            2,
                            GL_FLOAT,
                            GL_FALSE,
                            sizeof(Vertex),
                            (void*)offsetof(Vertex,texture));
}

void Plane::tick(float dt)
{
    model = glm::rotate(model, -10.0f * dt, glm::vec3(0,1,0));
}

void Plane::render()
{
    program->bind();
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    texture->bind(GL_TEXTURE0);

    glDrawArrays(GL_TRIANGLES, 0, geometry.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    program->unbind();
}

void Plane::scale(float scaleValue)
{
    model = glm::scale(model, glm::vec3(scaleValue,scaleValue,scaleValue));
}
