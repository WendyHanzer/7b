#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <glm/glm.hpp>

class Entity {
public:
    virtual ~Entity() {}

    virtual void init() = 0;
    virtual void tick(float dt) = 0;
    virtual void render() {}

    virtual void scale(float scaleValue) {}

    const glm::mat4& getModel() const {return model;}

protected:
    glm::mat4 model;
};

#endif // ENTITY_HPP