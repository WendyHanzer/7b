#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include "gl.hpp"

class Texture {
public:
    Texture(GLenum type);
    Texture(const std::string& fileName, GLenum type);
    virtual ~Texture();

    virtual void init();
    virtual void bind(GLenum textureUnit);

protected:
    std::string file_name;
    GLenum target;
    GLuint textureID;
};

#endif // TEXTURE_HPP