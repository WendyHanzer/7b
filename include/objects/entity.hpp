#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "vertex.hpp"
#include "gl.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

class Program;
class Texture;

class Entity {
public:
    Entity();
    Entity(Program *prog, const std::string& file, const std::string& textureFile = "");
    virtual ~Entity();

    void initWithFiles(const std::string& file, const std::string& textureFile);

    virtual void init();
    virtual void tick(float dt);
    virtual void render();

    virtual void scale(float scaleValue) {model = glm::scale(model, glm::vec3(scaleValue,scaleValue,scaleValue));}
    virtual void rotate(float angle, const glm::vec3& axis) {model = glm::rotate(model, angle, axis);}
    virtual void translate(const glm::vec3& amount) {model = glm::translate(model, amount);}

    const glm::mat4& getModel() const {return model;}

    int getWidth() const {return width;}
    int getHeight() const {return height;}
protected:
    int width, height;
    glm::mat4 model;
    std::vector<Vertex> geometry;

    Program *program;
    Texture *texture;

    GLuint vbo, vao;
};

#endif // ENTITY_HPP