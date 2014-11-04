#ifndef MESH_HPP
#define MESH_HPP

#include "vertex.hpp"

#include <string>
#include <vector>

class Mesh {
public:
    Mesh(const char *fileName);
    ~Mesh();

    void init();
    void render();

private:
    std::string mesh_file;
    std::vector<Vertex> geometry;
};

#endif // MESH_HPP
