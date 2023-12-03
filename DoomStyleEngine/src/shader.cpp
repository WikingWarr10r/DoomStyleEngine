#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexShaderSource = parseShader(vertexPath);
    std::string fragmentShaderSource = parseShader(fragmentPath);

    ID = createShader(vertexShaderSource, fragmentShaderSource);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setMat4(const std::string& name, const glm::mat4& matrix) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

std::string Shader::parseShader(const char* filePath) {
    std::ifstream shaderFile(filePath);
    std::stringstream shaderStream;

    if (!shaderFile.is_open()) {
        std::cout << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }

    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    return shaderStream.str();
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
