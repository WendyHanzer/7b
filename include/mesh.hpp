#ifndef MESH_HPP
#define MESH_HPP

class Mesh {
public:
    Mesh(const char *fileName);
    ~Mesh();

    void init(const char *fileName);
    void render();
};

#endif // MESH_HPP