#ifndef CUBE_HPP
#define CUBE_HPP

#include <vector>

#include <glm/glm.hpp>

#include "entity.hpp"
#include "vertex.hpp"

class Program;
class Texture;

class Cube : public Entity {
public:
    Cube(Program *prog, const glm::vec3& pos = glm::vec3(0.0f,0.0f,0.0f));
    virtual ~Cube();

    virtual void init();
    virtual void tick(float dt);
    virtual void render();

    virtual void scale(float scaleValue);

private:
    void initGeometry();

    std::vector<Vertex> geometry;
    Program *program;
    Texture *texture;

    GLuint vbo, vao;
};

#endif // CUBE_HPP
