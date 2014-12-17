#ifndef RANDOM_TEXTURE_HPP
#define RANDOM_TEXTURE_HPP

#include "texture.hpp"

class RandomTexture : public Texture {
public:
    RandomTexture(unsigned int rand_size, GLenum type);
    virtual ~RandomTexture();

    void init();
    void bind(GLenum textureUnit);

private:
    unsigned int size;
};

#endif // RANDOM_TEXTURE_HPP