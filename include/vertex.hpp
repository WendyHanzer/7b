#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "gl.hpp"

struct Vertex {
    GLfloat pos[3];
    GLfloat normal[3];
    GLfloat texture[2];

    Vertex() {}

    Vertex(const Vertex& other) {
        for(int i = 0; i < 3; i++) {
            pos[i] = other.pos[i];
            normal[i] = other.normal[i];
        }

        texture[0] = other.texture[0];
        texture[1] = other.texture[1];
    }
};

#endif // VERTEX_HPP
