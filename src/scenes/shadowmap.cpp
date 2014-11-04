#include "shadowmap.hpp"
#include "cube.hpp"
#include "plane.hpp"

ShadowMapScene::ShadowMapScene()
{

}

ShadowMapScene::~ShadowMapScene()
{

}

void ShadowMapScene::init()
{
    cube = new Cube(glm::vec3(0,10,0));
    //cube->scale(100.0f);
    ground = new Plane();
}

void ShadowMapScene::tick(float dt)
{
    ground->tick(dt);
    cube->tick(dt); 
}

void ShadowMapScene::render()
{
    ground->render();
    cube->render();
}

