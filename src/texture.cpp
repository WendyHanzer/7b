#include "texture.hpp"
#include "engine.hpp"

#include <iostream>

#include <FreeImagePlus.h>

Texture::Texture(const std::string& fileName, GLenum type)
    : file_name(fileName), target(type)
{
    init();
}

Texture::~Texture()
{

}

void Texture::init()
{
    fipImage image;
    if(image.load(file_name.c_str())) {
        if(image.getImageType() == FIT_UNKNOWN) {
            std::cerr << "Unknown image type for texture: " << file_name << std::endl;
            return;
        }

        image.convertTo32Bits();

        glGenTextures(1, &textureID);

        if(Engine::getEngine()->getOptions().verbose)
            std::cout << "TextureID: " << textureID << std::endl;

        glBindTexture(target, textureID);
        glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if(target == GL_TEXTURE_2D) {
            glTexImage2D(target, 0, GL_RGBA, image.getWidth(), image.getHeight(),
                0, GL_BGRA, GL_UNSIGNED_BYTE, (void*) image.accessPixels());
        }
        else {
            glTexImage1D(target, 0, GL_RGBA, image.getWidth(), 0,
                GL_BGRA, GL_UNSIGNED_BYTE, (void*) image.accessPixels());
        }

        glBindTexture(target, 0);
    }
}

void Texture::bind(GLenum textureUnit)
{
    glActiveTexture(textureUnit);
    glBindTexture(target, textureID);
}
