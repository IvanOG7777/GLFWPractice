//
// Created by elder on 6/26/2026.
//

#include <iostream>
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "../Header/GLUtils.h"
#include "../Header/Vector3.h"
#include "../Header/Geometry.h"


const char* vertexShader = R"GLSL(
    #version 330 core
    layout(location = 0) in vec3 aPos;

    uniform vec2 uResolution;
    uniform vec2 uOffset;
    uniform vec2 uScale;

    void main() {
        vec2 worldPosition = aPos * uScale + uOffset;

        vec2 NDC = worldPositon / uResolution;

        ndc = ndc * 2.0 - 1.0;

        gl_Position = vec4(ndc.x, ndc.y, 0.0, 1.0);
    }
)GLSL";

const char* fragmentShader = R"GLSL(
    #version 330 core

    out vec3 fragment;
    uniform vec3 uColor;

    void main() {
        fragment = vec4(uColor, 1.0);
    }
)GLSL";

int main() {

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!glfwInit()) {
        std::cerr << "GLFW INIT ERROR \n";
        return -1;
    }

    std:: vector<Vector3> grid = makeGrid(16);

    GLFWwindow *window = createWindow();
    glfwMakeContextCurrent(window);

    GLuint gridVAO = 0;
    GLuint gridVBO = 0;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShader, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, nullptr);
    glCompileShader(fs);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);

    glDeleteShader(vs);
    glDeleteShader(fs);

    glGenVertexArrays(1, &gridVAO);
    glGenBuffers(1, &gridVBO);

    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, grid.size() * sizeof(Vector3), grid.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}