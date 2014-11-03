#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include "gl.hpp"

class Texture {
public:
    Texture(const std::string& fileName, GLenum type);
    ~Texture();

    void init();
    void bind(GLenum textureUnit);

private:
    std::string file_name;
    GLenum target;
    GLuint textureID;
};

#endif // TEXTURE_HPP