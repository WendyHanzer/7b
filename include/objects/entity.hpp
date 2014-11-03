#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity {
public:
    virtual ~Entity() {}

    virtual void init() = 0;
    virtual void tick(float dt) = 0;
    virtual void render() {}

    virtual void scale(float scaleValue) {}
};

#endif // ENTITY_HPP