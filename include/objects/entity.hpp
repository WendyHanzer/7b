#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Entity {
public:
    virtual ~Entity() {}

    virtual void init() = 0;
    virtual void tick(float dt) = 0;
    virtual void render() {}

    virtual void scale(float scaleValue) {model = glm::scale(model, glm::vec3(scaleValue,scaleValue,scaleValue));}
    virtual void rotate(float angle, const glm::vec3& axis) {model = glm::rotate(model, angle, axis);}
    virtual void translate(const glm::vec3& amount) {model = glm::translate(model, amount);}

    const glm::mat4& getModel() const {return model;}

protected:
    glm::mat4 model;
};

#endif // ENTITY_HPP