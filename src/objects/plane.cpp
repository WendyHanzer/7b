#include "plane.hpp"
#include "texture.hpp"
#include "engine.hpp"
#include "graphics.hpp"
#include "programs/lighting.hpp"
#include "gl.hpp"
#include "mesh.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Plane::Plane(Program *prog, const std::string& texture, int plane_width, int plane_height)
{
    program = prog;
    textureFile = texture;
    density = 1.0f;

    width = plane_width;
    height = plane_height;

    init();
}

Plane::~Plane()
{

}

void Plane::init()
{
    texture = new Texture(textureFile.c_str(), GL_TEXTURE_2D);

    Vertex vert;

    //geometry.clear();
    //geometry.resize((width / density) * (height / density));

    vert.normal[0] = 0;
    vert.normal[1] = 1;
    vert.normal[2] = 0;

    for(float x = 0.0f; x < width; x += density) {
        for(float z = 0.0f; z < height; z += density) {
            vert.pos[0] = x;
            vert.pos[1] = 0 /*dist(gen)*/;
            vert.pos[2] = z;

            vert.texture[0] = x/(float)width;
            vert.texture[1] = z/(float)height;

            geometry.push_back(vert);
        }
    }

    unsigned int scaledWidth = width/density, scaledHeight = height/density;
    //indices.clear();
    //indices.reserve(scaledWidth * scaledHeight);
    for(int x = 0; x < scaledWidth - 1; x++) {
        for(int z = 0; z < scaledHeight - 1; z++) {
            indices.push_back(z * scaledHeight + x);
            indices.push_back((z*scaledHeight) + x + 1);
            indices.push_back((z+1) * scaledHeight + x);

            indices.push_back((z * scaledHeight) + x + 1);
            indices.push_back((z+1) * scaledHeight + x + 1);
            indices.push_back((z + 1) * scaledHeight + x);
        }
    }

    //geometry = Mesh::load("../assets/objects/plane.ply");

    // for(auto& vertex : geometry) {
    //     vertex.texture[0] = vertex.pos[0] / 10.0f;
    //     vertex.texture[1] = vertex.pos[2] / 10.0f;
    // }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * geometry.size(), geometry.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &vio);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

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
    //model = glm::rotate(model, -10.0f * dt, glm::vec3(0,1,0));
    // for(float x = 0.0f; x < width; x += density)
    //     for(float z = 0.0f; z < height; z += density)
    //         calcNormal(x,z, geometry[x*width+z]);
}

void Plane::render()
{
    program->bind();
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    texture->bind(GL_TEXTURE0);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
    //glDrawArrays(GL_TRIANGLES, 0, geometry.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    program->unbind();
}

void Plane::scale(float scaleValue)
{
    model = glm::scale(model, glm::vec3(scaleValue,1.0,scaleValue));
}

void Plane::calcNormal(int x, int z, Vertex& vert)
{
    glm::vec3 normal, center, up, down, left, right;

    if(x > 0 && z > 0) {
        center = glm::vec3(vert.pos[0], vert.pos[1], vert.pos[2]);

        up.z = z + 1;
        up.x = x;
        up.y = 0.0f;

        down.z = z - 1;
        down.x = x;
        down.y = 0.0f;

        left.z = z;
        left.x = x - 1;
        left.y = 0.0f;

        right.z = z;
        right.x = x + 1;
        right.y = 0.0f;

        normal += glm::cross(up-center, right-center);
        normal += glm::cross(right-center, down-center);
        normal += glm::cross(down-center, left-center);
        normal += glm::cross(left-center, up-center);
        normal = glm::normalize(normal);

        vert.normal[0] = normal.x;
        vert.normal[1] = normal.y;
        vert.normal[2] = normal.z;
    }

}