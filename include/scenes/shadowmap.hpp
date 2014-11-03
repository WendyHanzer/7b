#ifndef SHADOW_MAP_SCENE_HPP
#define SHADOW_MAP_SCENE_HPP

#include "scene.hpp"

class Cube;
class Plane;

class ShadowMapScene : public Scene {
public:
    ShadowMapScene();
    ~ShadowMapScene();
    virtual void init();
    virtual void tick(float dt);
    virtual void render();

private:
    Cube *cube;
    Plane *ground;
};

#endif // SHADOW_MAP_SCENE_HPP