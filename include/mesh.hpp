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

    static std::vector<Vertex> load(const std::string& fileName);
};

#endif // MESH_HPP
