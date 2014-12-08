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

    if(flag) delete flag;
}

void ShadowMapScene::init()
{
    lighting_program = Engine::getEngine()->graphics->getShaderProgram("lighting");
    flag_program = Engine::getEngine()->graphics->getShaderProgram("flag");

    cube = new Cube(lighting_program, glm::vec3(0,10,0));
    //cube->scale(100.0f);
    ground = new Plane(lighting_program, "../assets/desert2.jpg");

    flag = new Plane(flag_program, "../assets/flag.jpg");
    flag->rotate(90, glm::vec3(1,0,0));
    flag->translate(glm::vec3(0,50,0));
    //flag->scale(100);
    //terrain = new GDALTerrain(lighting_program, "../assets/DryCreek/DCEWsqrExtent.tif");

    dirLight = new DirectionalLight(glm::vec3(1,1,1), glm::vec3(0,-1,0), 0.1f, 0.9f);
    pointLight = new PointLight(glm::vec3(1,1,1), glm::vec3(0,1,0), 0.1f, 0.9f);

    entities = {cube, ground, flag};
    programs = {lighting_program, flag_program};
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
    static float waveTime = 0.2f, waveWidth = 0.2f, waveHeight = 3.0f, waveFreq = 0.05f;

    auto camera = Engine::getEngine()->graphics->camera;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(Program *prog : programs) {
        prog->bind();
        prog->set("ambientIntensity", dirLight->intensity);
        prog->set("diffuseIntensity", dirLight->diffIntensity);
        prog->set("light_dir", dirLight->direction);
        prog->set("pointLightPos", pointLight->pos);
        //prog->set("specularIntensity", 0.3f);
        //prog->set("specularPower", 0.3f);
        prog->set("cameraPos", camera->getPos());
        prog->set("spotLightDir", camera->getOrientation());
        prog->set("tex", 0);
        prog->unbind();
    }

    waveTime += waveFreq;

    auto& view = Engine::getEngine()->graphics->view;
    auto& proj = Engine::getEngine()->graphics->projection;
    for(Entity *ent : entities) {
        const auto& model = ent->getModel();
        glm::mat4 mvp = proj * view * model;


        lighting_program->bind();
        lighting_program->set("mvp", mvp);
        lighting_program->set("modelMatrix", model);
        lighting_program->unbind();

        flag_program->bind();
        flag_program->set("mvp", mvp);
        flag_program->set("modelMatrix", model);
        flag_program->set("waveTime", waveTime);
        flag_program->set("waveWidth", waveWidth);
        flag_program->set("waveHeight", waveHeight);
        flag_program->unbind();
        ent->render();
    }

    //lighting_program->unbind();
}

