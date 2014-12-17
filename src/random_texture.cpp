#include "random_texture.hpp"

#include <random>

struct R_Vec3 {
    float x,y,z;
};

RandomTexture::RandomTexture(unsigned int rand_size, GLenum type)
    : Texture(type), size(rand_size)
{
    init();
}

RandomTexture::~RandomTexture()
{

}

void RandomTexture::init()
{
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> dist;

    R_Vec3 *data = new R_Vec3[size];
    for(unsigned int i = 0; i < size; i++) {
        data[i].x = dist(eng);
        data[i].y = dist(eng);
        data[i].z = dist(eng);
    }

    glGenTextures(1, &textureID);
    glBindTexture(target, textureID);
    glTexImage1D(target, 0, GL_RGB, size, 0, GL_RGB, GL_FLOAT, data);
    glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(target, GL_TEXTURE_WRAP_S, GL_REPEAT);

    delete[] data;
}

void RandomTexture::bind(GLenum textureUnit)
{
    glActiveTexture(textureUnit);
    glBindTexture(target, textureID);
}
