#include "gbuffer.hpp"
#include "engine.hpp"
#include "graphics.hpp"

#include <iostream>

GBuffer::GBuffer()
{
}

GBuffer::~GBuffer()
{
}

void GBuffer::init()
{
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

    glGenTextures((GLsizei)textures.size(), textures.data());
    glGenTextures(1, &depthTexture);

    int width, height;
    Engine::getEngine()->graphics->getWindowSize(width, height);

    for(unsigned i = 0; i < textures.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures[i], 0);
    }

    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

    GLenum drawBuffers[] = {
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1,
        GL_COLOR_ATTACHMENT2,
        GL_COLOR_ATTACHMENT3
    };

    glDrawBuffers(4, drawBuffers);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Unable to initialize framebuffer in: " << __FUNCTION__ << std::endl;
        exit(1);
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void GBuffer::bindForWriting()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
}

void GBuffer::bindForReading()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
}

void GBuffer::setReadBuffer(GBufferTextureType textureType)
{
    glReadBuffer(GL_COLOR_ATTACHMENT0 + textureType);
}
