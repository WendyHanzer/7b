#ifndef SHADOW_MAP_SCENE_HPP
#define SHADOW_MAP_SCENE_HPP

#include "scene.hpp"
#include "light.hpp"

#include <vector>

class Cube;
class Plane;
class Program;
class Entity;

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
    Program *program;

    float lightAngle;
    DirectionalLight *dirLight;
    PointLight *pointLight;
    //std::vector<Light*> lights;
    std::vector<Entity*> entities;
};

#endif // SHADOW_MAP_SCENE_HPP