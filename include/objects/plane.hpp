#ifndef PLANE_HPP
#define PLANE_HPP

#include <vector>

#include <glm/glm.hpp>

#include "entity.hpp"
#include "vertex.hpp"

class Program;
class Texture;

class Plane : public Entity {
public:
    Plane(Program *prog, int width = 200, int height = 200);
    virtual ~Plane();

    virtual void init();
    virtual void tick(float dt);
    virtual void render();

    virtual void scale(float scaleValue);

private:
    void initGeometry();

    std::vector<Vertex> geometry;
    Program *program;
    Texture *texture;
    glm::mat4 model;

    GLuint vbo, vao;
};

#endif // PLANE_HPP
