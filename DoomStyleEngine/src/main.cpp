#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <sstream>

#include "quad.h"
#include "shader.h"
#include "camera.h"
#include "quadbatch.h"
#include "texture.h"

int main(void) {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Engine", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Glew OK Failed" << std::endl;

    std::cout << "Running OpenGL Version " << glGetString(GL_VERSION);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    std::cout << " on " << vendor << " " << renderer << std::endl;

    QuadBatch quadBatch;

    std::vector<glm::vec3> quadVertices1 = quadBatch.generateVertices(glm::vec3(-0.5f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f), 1.0f);
    std::vector<glm::vec3> quadVertices2 = quadBatch.generateVertices(glm::vec3(-0.5f, 0.0f, 1.0f), glm::vec3(0.5f, 0.0f, 1.0f), 1.0f);

    std::vector<glm::vec2> texCoords1 = QuadBatch::generateTextureCoords();
    std::vector<glm::vec2> texCoords2 = QuadBatch::generateTextureCoords();

    quadBatch.addQuad(quadVertices1, texCoords1);
    quadBatch.addQuad(quadVertices2, texCoords2);

    Texture texture;
    if (!texture.loadTexture("res/textures/cobble.png")) {
        std::cout << "Failed to load texture" << std::endl;
    }

    Shader shader("res/shaders/default.vert", "res/shaders/default.frag");

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double lastTime = 0;
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;

        double fps = 1 / deltaTime;

        std::ostringstream ss;
        ss << "Engine | FPS: " << static_cast<int>(fps);
        glfwSetWindowTitle(window, ss.str().c_str());

        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        texture.bind();

        glm::mat4 model = glm::mat4(1.0f);
        shader.setMat4("u_Model", model);

        glm::mat4 view = camera.getViewMatrix();
        shader.setMat4("u_View", view);

        float aspectRatio = 640.0f / 480.0f;
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
        shader.setMat4("u_Projection", projection);

        quadBatch.render();

        camera.processInput(window, deltaTime);

        glfwSwapBuffers(window);
        glfwPollEvents();
        lastTime = currentTime;
    }

    glfwTerminate();
    return 0;
}