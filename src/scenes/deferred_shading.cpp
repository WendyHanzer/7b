#include "deferred_shading.hpp"
#include "deferred_shading_prog.hpp"
#include "cube.hpp"
#include "plane.hpp"
#include "gbuffer.hpp"
#include "engine.hpp"
#include "graphics.hpp"

#include <iostream>

DeferredShadingScene::DeferredShadingScene()
{
}

DeferredShadingScene::~DeferredShadingScene()
{
}

void DeferredShadingScene::init()
{
    Engine::getEngine()->graphics->getWindowSize(windowWidth, windowHeight);
    program = Engine::getEngine()->graphics->getShaderProgram("deferred_shading");
    gbuffer = new GBuffer();
    gbuffer->init();

    cube = new Cube(program, glm::vec3(0,10,0));
    //cube->scale(100.0f);
    ground = new Plane(program);

    entities = {cube, ground};
}

void DeferredShadingScene::tick(float dt)
{
    for(Entity *ent : entities) {
        ent->tick(dt);
    }
}

void DeferredShadingScene::render()
{
    program->bind();
    gbuffer->bindForWriting();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto& view = Engine::getEngine()->graphics->view;
    auto& proj = Engine::getEngine()->graphics->projection;
    for(Entity *ent : entities) {
        const auto& model = ent->getModel();
        glm::mat4 mvp = proj * view * model;

        program->set("mvp", mvp);
        program->set("modelMatrix", model);
        ent->render();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gbuffer->bindForReading();

    GLsizei halfW = (GLsizei) (windowWidth / 2.0f);
    GLsizei halfH = (GLsizei) (windowHeight / 2.0f);

    gbuffer->setReadBuffer(GBuffer::GBUFFER_TEXTURE_POSITION);
    glBlitFramebuffer(0, 0, windowWidth, windowHeight, 0, 0, halfW, halfH, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    gbuffer->setReadBuffer(GBuffer::GBUFFER_TEXTURE_DIFFUSE);
    glBlitFramebuffer(0,0, windowWidth, windowHeight, 0, halfH, halfW, windowHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    gbuffer->setReadBuffer(GBuffer::GBUFFER_TEXTURE_NORMAL);
    glBlitFramebuffer(0,0, windowWidth, windowHeight, halfW, halfH, windowWidth, windowHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    gbuffer->setReadBuffer(GBuffer::GBUFFER_TEXTURE_TEXCOORD);
    glBlitFramebuffer(0, 0, windowWidth, windowHeight, halfW, 0, windowWidth, halfH, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    program->unbind();
}

void DeferredShadingScene::scale(float scaleValue)
{

}
