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
#include "../Header/Matrix4.h"
#include "../Header/Constants.h"


const char* vertexShader = R"GLSL(
    #version 330 core
    layout(location = 0) in vec3 aPos;

    uniform vec2 uResolution;
    uniform vec2 uOffset;
    uniform float uScale;

    void main() {
        vec2 worldPositon = aPos.xy * uScale + uOffset;

        vec2 ndc = worldPositon / uResolution;

        ndc = ndc * 2.0 - 1.0;

        gl_Position = vec4(ndc.x, ndc.y, 0.0, 1.0);
    }
)GLSL";

const char* fragmentShader = R"GLSL(
    #version 330 core

    out vec4 fragment;
    uniform vec3 uColor;

    void main() {
        fragment = vec4(uColor, 1.0);
    }
)GLSL";

float toRadians(float angleDegrees) {
    return angleDegrees * (PI/180.0f);
}

int main() {

    Matrix4 matrixRotationY = Matrix4::makeRotationY(toRadians(180.0f));
    Matrix4 matrixRotationX = Matrix4::makeRotationX(toRadians(90.0f));
    std:: cout << "rotationY" << std:: endl;
    matrixRotationY.print();
    std:: cout << std:: endl;
    std:: cout << "rotationX" << std:: endl;
    matrixRotationX.print();
    std:: cout << std:: endl;

    Vector4 point(0,1,0,1);
    std:: cout << "Before y and x rotation \n";
    std:: cout << point << std:: endl;
    std:: cout << std:: endl;

    auto resultY = matrixRotationY * point;
    auto resultX = matrixRotationX * point;

    std:: cout << "After y rotation \n";
    std:: cout << resultY << std:: endl;
    std:: cout << std:: endl;

    std:: cout << "After x rotation \n";
    std:: cout << resultX << std:: endl;
    std:: cout << std:: endl;

    return 0;

    if (!glfwInit()) {
        std::cerr << "GLFW INIT ERROR \n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std:: vector<Vector3> grid = makeGrid(4);
    std::vector<Vector3> square = makeSquare();

    GLFWwindow *window = createWindow();
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "GLAD INIT ERROR\n";
        return -1;
    }

    GLuint gridVAO = 0, squareVAO = 0;
    GLuint gridVBO = 0, squareVBO = 0;

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

    GLuint uResolutionLoc = glGetUniformLocation(shaderProgram, "uResolution");
    GLuint uColorLoc = glGetUniformLocation(shaderProgram, "uColor");
    GLuint uOffsetLoc = glGetUniformLocation(shaderProgram, "uOffset");
    GLuint uScaleLoc = glGetUniformLocation(shaderProgram, "uScale");

    glGenVertexArrays(1, &gridVAO);
    glGenBuffers(1, &gridVBO);
    glGenVertexArrays(1, &squareVAO);
    glGenBuffers(1, &squareVBO);


    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBindVertexArray(squareVAO);
    glBindBuffer(GL_ARRAY_BUFFER, squareVBO);

    glBufferData(GL_ARRAY_BUFFER, grid.size() * sizeof(Vector3), grid.data(), GL_DYNAMIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, square.size() * sizeof(Vector3), square.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        int w = W;
        int h = H;
        glfwGetFramebufferSize(window, &w, &h);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glUniform2f(uResolutionLoc, w, h);

        // glBindVertexArray(gridVAO);
        // glUniform3f(uColorLoc, 1.0f, 1.0f, 1.0f);
        // glUniform2f(uOffsetLoc, 0.0f, 0.0f);
        // glUniform1f(uScaleLoc, 1.0f);
        //
        // glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(grid.size()));

        glBindVertexArray(squareVAO);
        glUniform3f(uColorLoc, 0.0f, 1.0f, 1.0f);
        glUniform2f(uOffsetLoc, 0.0f, 0.0f);
        glUniform1f(uScaleLoc, 1.0f);

        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(square.size()));

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}