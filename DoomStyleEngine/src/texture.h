#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>

class Texture {
public:
    Texture();
    ~Texture();

    bool loadTexture(const std::string& fileName);
    void bind(unsigned int unit = 0);
    void unbind();

private:
    GLuint m_textureID;
};

#endif 