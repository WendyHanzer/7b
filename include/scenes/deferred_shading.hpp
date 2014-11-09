#ifndef Deferred_SHADING_HPP
#define Deferred_SHADING_HPP

#include "scene.hpp"
#include <vector>

class Program;
class Cube;
class Plane;
class GBuffer;
class Entity;

class DeferredShadingScene : public Scene {

public:
    DeferredShadingScene();
    virtual ~DeferredShadingScene();

    virtual void init();
    virtual void tick(float dt);
    virtual void render();
    virtual void scale(float scaleValue);

private:
    Program *program;
    GBuffer *gbuffer;

    Cube *cube;
    Plane *ground;

    int windowWidth, windowHeight;

    std::vector<Entity*> entities;
};

#endif // Deferred_SHADING_HPP

