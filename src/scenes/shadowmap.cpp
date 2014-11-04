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
    cube = new Cube();
    cube->scale(100.0f);
}

void ShadowMapScene::tick(float dt)
{
    cube->tick(dt);
}

void ShadowMapScene::render()
{
    cube->render();
}

