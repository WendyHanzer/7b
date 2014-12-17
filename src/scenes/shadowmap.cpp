#include "shadowmap.hpp"
#include "cube.hpp"
#include "plane.hpp"
#include "program.hpp"
#include "engine.hpp"
#include "graphics.hpp"
#include "camera.hpp"
#include "input.hpp"
#include "gdalterrain.hpp"
#include "particles.hpp"

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
    prog_update = Engine::getEngine()->graphics->getShaderProgram("particles_update");
    prog_render = Engine::getEngine()->graphics->getShaderProgram("particles_render");

    //cube = new Cube(lighting_program, glm::vec3(0,10,0));
    //cube->scale(100.0f);
    //ground = new Plane(lighting_program, "../assets/dirt.png", 1000, 1000);
    //ground->translate(glm::vec3(-ground->getWidth()/2, 0, -ground->getHeight()/2));

    flag = new Plane(flag_program, "../assets/flag.jpg", 15, 15);
    flag->translate(glm::vec3(1,90,0));
    flag->rotate(90, glm::vec3(1,0,0));
    //flag->scale(100);

    flag_pole = new Entity(lighting_program, "../assets/objects/flagpole.obj", "../assets/gray.jpg");
    flag_pole->translate(glm::vec3(0,50,0));
    terrain = new GDALTerrain(lighting_program, "../assets/DryCreek/DCEWsqrExtent.tif");
    terrain->center();

    particle_system = new ParticleSystem(prog_update, prog_render);
    particle_system->initWithPos(glm::vec3(0));

    dirLight = new DirectionalLight(glm::vec3(1,1,1), glm::vec3(0,-1,0), 0.1f, 0.9f);
    pointLight = new PointLight(glm::vec3(1,1,1), glm::vec3(0,1,0), 0.1f, 0.9f);

    entities = {terrain, flag_pole, flag};
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

    currentDT = dt;
}

void ShadowMapScene::render()
{
    static float waveTime = 0.2f, waveWidth = 0.2f, waveHeight = 3.0f, waveFreq = 0.05f;

    auto camera = Engine::getEngine()->graphics->camera;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(Engine::getEngine()->getOptions().loading_done)
        particle_system->renderWithDT(currentDT);

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

