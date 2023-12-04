#ifndef QUAD_BATCH_H
#define QUAD_BATCH_H

#include <vector>
#include "quad.h"

class QuadBatch {
public:
    QuadBatch();
    ~QuadBatch();

    void addQuad(const std::vector<glm::vec3>& quadPoints);
    void render() const;

    static std::vector<glm::vec3> generateVertices(glm::vec3 startPoint, glm::vec3 endPoint, float height);

private:
    std::vector<std::vector<glm::vec3>> quadVertices;
    unsigned int VAO; 
    unsigned int VBO; 
};

#endif
