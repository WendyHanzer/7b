#include "shadowmap.hpp"
#include "cube.hpp"
#include "plane.hpp"
#include "program.hpp"
#include "engine.hpp"
#include "graphics.hpp"
#include "camera.hpp"
#include "input.hpp"
#include "gdalterrain.hpp"

#include <glm/glm.hpp>
#include <SDL_keycode.h>

#include <iostream>

ShadowMapScene::ShadowMapScene()
{

}

ShadowMapScene::~ShadowMapScene()
{
    if(cube) delete cube;
    if(ground) delete ground;
    if(terrain) delete terrain;
    if(dirLight) delete dirLight;
    if(pointLight) delete pointLight;
}

void ShadowMapScene::init()
{
    program = Engine::getEngine()->graphics->getShaderProgram("lighting");

    //cube = new Cube(program, glm::vec3(0,10,0));
    //cube->scale(100.0f);
    //ground = new Plane(program);
    terrain = new GDALTerrain(program, "../assets/DryCreek/DCEWsqrExtent.tif");

    dirLight = new DirectionalLight(glm::vec3(1,1,1), glm::vec3(0,-1,0), 0.1f, 0.9f);
    pointLight = new PointLight(glm::vec3(1,1,1), glm::vec3(0,1,0), 0.1f, 0.9f);

    entities = {terrain};//{cube, ground};
}

void ShadowMapScene::tick(float dt)
{
    for(Entity *ent : entities) {
        ent->tick(dt);
    }

    auto engine = Engine::getEngine();

    if(engine->input->getKeyMap().at(SDLK_LEFT)) {
        lightAngle -= engine->getOptions().light_speed;
    }

    else if(engine->input->getKeyMap().at(SDLK_RIGHT)) {
        lightAngle += engine->getOptions().light_speed;
    }

    float y = -cosf(lightAngle + 1.57f);
    float x = -sinf(lightAngle + 1.57f);

    dirLight->direction = glm::vec3(x,y,0.0f);
}

void ShadowMapScene::render()
{
    auto camera = Engine::getEngine()->graphics->camera;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program->bind();
    program->set("ambientIntensity", dirLight->intensity);
    program->set("diffuseIntensity", dirLight->diffIntensity);
    program->set("light_dir", dirLight->direction);
    program->set("pointLightPos", pointLight->pos);
    //program->set("specularIntensity", 0.3f);
    //program->set("specularPower", 0.3f);
    program->set("cameraPos", camera->getPos());
    program->set("spotLightDir", camera->getOrientation());
    program->set("tex", 0);

    auto& view = Engine::getEngine()->graphics->view;
    auto& proj = Engine::getEngine()->graphics->projection;
    for(Entity *ent : entities) {
        const auto& model = ent->getModel();
        glm::mat4 mvp = proj * view * model;

        program->set("mvp", mvp);
        program->set("modelMatrix", model);
        ent->render();
    }

    program->unbind();
}

