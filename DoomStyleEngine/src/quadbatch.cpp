#include "quadbatch.h"
#include <GL/glew.h>

QuadBatch::QuadBatch() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW); 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

QuadBatch::~QuadBatch() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    quadVertices.clear();
}

void QuadBatch::addQuad(const std::vector<glm::vec3>& quadPoints) {
    quadVertices.push_back(quadPoints);
}

void QuadBatch::render() const {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    size_t totalSize = 0;
    for (const auto& quad : quadVertices) {
        totalSize += quad.size() * sizeof(glm::vec3);
    }

    glBufferData(GL_ARRAY_BUFFER, totalSize, nullptr, GL_DYNAMIC_DRAW);

    size_t offset = 0;
    for (const auto& quad : quadVertices) {
        glBufferSubData(GL_ARRAY_BUFFER, offset, quad.size() * sizeof(glm::vec3), quad.data());
        offset += quad.size() * sizeof(glm::vec3);
    }

    for (size_t i = 0; i < quadVertices.size(); ++i) {
        Quad quad(quadVertices[i]);
        quad.render();
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

std::vector<glm::vec3> QuadBatch::generateVertices(glm::vec3 startPoint, glm::vec3 endPoint, float height) {
    glm::vec3 lowStart = glm::vec3(startPoint.x, -height / 2, startPoint.z);
    glm::vec3 lowEnd = glm::vec3(endPoint.x, -height / 2, endPoint.z);

    glm::vec3 highEnd = glm::vec3(endPoint.x, height / 2, endPoint.z);
    glm::vec3 highStart = glm::vec3(startPoint.x, height / 2, startPoint.z);

    std::vector<glm::vec3> quadVertices = {
        lowStart,
        lowEnd,
        highEnd,
        highStart
    };

    return quadVertices;
}
