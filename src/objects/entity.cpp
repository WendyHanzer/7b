#include "entity.hpp"
#include "texture.hpp"
#include "program.hpp"
#include "mesh.hpp"

Entity::Entity()
{

}

Entity::Entity(Program *prog, const std::string& file, const std::string& textureFile)
{
    program = prog;
    texture = nullptr;
    initWithFiles(file, textureFile);
}

Entity::~Entity()
{

}

void Entity::initWithFiles(const std::string& file, const std::string& textureFile)
{
    if(textureFile != "")
        texture = new Texture(textureFile, GL_TEXTURE_2D);

    geometry = Mesh::load(file);

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

    glBindVertexArray(0);

}

void Entity::init()
{

}

void Entity::tick(float dt)
{

}

void Entity::render()
{
    program->bind();
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    if(texture) texture->bind(GL_TEXTURE0);

    glDrawArrays(GL_TRIANGLES, 0, geometry.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    program->unbind();
}