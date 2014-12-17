#ifndef PLANE_HPP
#define PLANE_HPP

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "entity.hpp"
#include "vertex.hpp"

class Program;
class Texture;

class Plane : public Entity {
public:
    Plane(Program *prog, const std::string& texture, int plane_width = 200, int plane_height = 200);
    virtual ~Plane();

    virtual void init();
    virtual void tick(float dt);
    virtual void render();

    virtual void scale(float scaleValue);

private:
    void calcNormal(int x, int z, Vertex& vert);

    std::vector<unsigned int> indices;
    Program *program;
    Texture *texture;
    glm::mat4 model;

    std::string textureFile;
    GLuint vio;
    float density;
};

#endif // PLANE_HPP
