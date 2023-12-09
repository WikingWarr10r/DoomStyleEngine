#ifndef QUAD_BATCH_H
#define QUAD_BATCH_H

#include <vector>
#include "quad.h"

class QuadBatch {
public:
    QuadBatch();
    ~QuadBatch();

    void addQuad(const std::vector<glm::vec3>& quadPoints, const std::vector<glm::vec2>& texCoords);
    void render() const;
    void reorderQuads(const glm::vec3& cameraPosition);

    static std::vector<glm::vec3> generateVertices(glm::vec3 startPoint, glm::vec3 endPoint, float height);
    static std::vector<glm::vec2> generateTextureCoords();

private:
    std::vector<std::vector<glm::vec3>> quadVertices;
    std::vector<std::vector<glm::vec2>> quadTextureCoords;
    unsigned int VAO;
    unsigned int VBO;

    glm::vec3 calculateMidpoint(const std::vector<glm::vec3>& quad);
};

#endif