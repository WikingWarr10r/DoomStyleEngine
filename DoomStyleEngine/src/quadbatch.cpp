#include "quadbatch.h"
#include <GL/glew.h>
#include <algorithm> 
#include <glm/gtx/norm.hpp>

QuadBatch::QuadBatch() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW); 

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

QuadBatch::~QuadBatch() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    quadVertices.clear();
}

void QuadBatch::addQuad(const std::vector<glm::vec3>& quadPoints, const std::vector<glm::vec2>& texCoords) {
    quadVertices.push_back(quadPoints);
    quadTextureCoords.push_back(texCoords);
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
    for (size_t i = 0; i < quadVertices.size(); ++i) {
        glBufferSubData(GL_ARRAY_BUFFER, offset, quadVertices[i].size() * sizeof(glm::vec3), quadVertices[i].data());
        offset += quadVertices[i].size() * sizeof(glm::vec3);
    }

    glBufferData(GL_ARRAY_BUFFER, quadTextureCoords.size() * sizeof(glm::vec2), quadTextureCoords.data(), GL_DYNAMIC_DRAW);

    for (size_t i = 0; i < quadVertices.size(); ++i) {
        Quad quad(quadVertices[i], quadTextureCoords[i]);
        quad.render();
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void QuadBatch::reorderQuads(const glm::vec3& cameraPosition) {
    std::vector<std::pair<float, size_t>> distances;
    distances.reserve(quadVertices.size());

    for (size_t i = 0; i < quadVertices.size(); ++i) {
        glm::vec3 midpoint = calculateMidpoint(quadVertices[i]);

        float distanceSquared = glm::length2(midpoint - cameraPosition);

        distances.emplace_back(distanceSquared, i);
    }

    std::sort(distances.rbegin(), distances.rend());

    std::vector<std::vector<glm::vec3>> sortedQuads;
    std::vector<std::vector<glm::vec2>> sortedTexCoords;

    sortedQuads.reserve(quadVertices.size());
    sortedTexCoords.reserve(quadTextureCoords.size());

    for (const auto& dist : distances) {
        sortedQuads.push_back(quadVertices[dist.second]);
        sortedTexCoords.push_back(quadTextureCoords[dist.second]);
    }

    quadVertices = sortedQuads;
    quadTextureCoords = sortedTexCoords;
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

std::vector<glm::vec2> QuadBatch::generateTextureCoords() {
    std::vector<glm::vec2> textureCoords = {
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f)
    };

    return textureCoords;
}

glm::vec3 QuadBatch::calculateMidpoint(const std::vector<glm::vec3>& quad) {
    glm::vec3 sum(0.0f);
    for (const auto& vertex : quad) {
        sum += vertex;
    }
    return sum / static_cast<float>(quad.size());
}