#ifndef QUAD_H
#define QUAD_H

#include <vector>
#include <glm/glm.hpp>

class Quad {
public:
    Quad(const std::vector<glm::vec3>& quadPoints, const std::vector<glm::vec2>& texCoords);
    void render() const;
    ~Quad();

private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textureCoords;
    unsigned int VBO, VAO, EBO;

    void setupQuad(const std::vector<glm::vec3>& quadPoints, const std::vector<glm::vec2>& texCoords);
    void setupBuffers();
};

#endif