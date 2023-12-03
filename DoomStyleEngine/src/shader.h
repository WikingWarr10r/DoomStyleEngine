#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void use();
    void setMat4(const std::string& name, const glm::mat4& matrix);

private:
    unsigned int ID;

    std::string parseShader(const char* filePath);
    unsigned int compileShader(unsigned int type, const std::string& source);
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
};

#endif