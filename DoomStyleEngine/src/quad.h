#ifndef QUAD_H
#define QUAD_H

#include <vector>
#include <glm/glm.hpp>

class Quad {
public:
    Quad(const std::vector<glm::vec3>& quadPoints);
    void render() const;
    ~Quad();

private:
    std::vector<glm::vec3> vertices;
    unsigned int VBO, VAO, EBO;

    void setupQuad(const std::vector<glm::vec3>& quadPoints);
    void setupBuffers();
};

#endif