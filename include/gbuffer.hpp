#ifndef GBUFFER_HPP
#define GBUFFER_HPP

#include "gl.hpp"

#include <array>

class GBuffer {
public:
    enum GBufferTextureType {
        GBUFFER_TEXTURE_POSITION,
        GBUFFER_TEXTURE_DIFFUSE,
        GBUFFER_TEXTURE_NORMAL,
        GBUFFER_TEXTURE_TEXCOORD,

        GBUFFER_TEXTURE_COUNT
    };

    GBuffer();
    ~GBuffer();

    void init();
    void bindForWriting();
    void bindForReading();

    void setReadBuffer(GBufferTextureType textureType);

private:
    GLuint fbo;
    std::array<GLuint, GBUFFER_TEXTURE_COUNT> textures;
    GLuint depthTexture;
};


#endif // GBUFFER_HPP