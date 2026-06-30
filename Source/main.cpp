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
    if (!glfwInit()) {
        std::cerr << "GLFW INIT ERROR \n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int currentAngle = 0;
    Matrix4 translation = Matrix4::makeTranslation(600, 200, 0);
    Matrix4 x = Matrix4::makeRotationY(toRadians(280));
    Matrix4 z = Matrix4::makeRotationZ(toRadians(45));

    Matrix4 perspectiveMatrix = Matrix4::makePerspective(toRadians(45), W/H, 0.1, 1000);
    std:: cout << toRadians(45) << std::endl;
    perspectiveMatrix.print();
    return 0;


    std::vector<Vector3> grid = makeGrid(4);
    std::vector<Vector3> square = makeSquare();
    std::vector<Vector3> transformedSquare;
    std::vector<Vector3> transformedXSquare;

    for (auto &vect : square) {
        Vector4 vect4(vect.x, vect.y, vect.z, 1);
        auto transformed = translation * vect4;
        transformedSquare.emplace_back(transformed.x, transformed.y, transformed.z);
    }

    for (auto &vect : transformedSquare) {
        Vector4 vect4(vect.x, vect.y, vect.z, 1);
        auto trans = z * vect4;
        transformedXSquare.emplace_back(trans.x, trans.y, trans.z);
    }


    GLFWwindow *window = createWindow();
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "GLAD INIT ERROR\n";
        return -1;
    }

    GLuint gridVAO = 0, squareVAO = 0, tSquareVAO = 0, tXSquareVAO = 0;
    GLuint gridVBO = 0, squareVBO = 0, tSquareVBO = 0, tXSquareVBO = 0;

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
    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, grid.size() * sizeof(Vector3), grid.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &squareVAO);
    glGenBuffers(1, &squareVBO);
    glBindVertexArray(squareVAO);
    glBindBuffer(GL_ARRAY_BUFFER, squareVBO);
    glBufferData(GL_ARRAY_BUFFER, square.size() * sizeof(Vector3), square.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &tSquareVAO);
    glGenBuffers(1, &tSquareVBO);
    glBindVertexArray(tSquareVAO);
    glBindBuffer(GL_ARRAY_BUFFER, tSquareVBO);
    glBufferData(GL_ARRAY_BUFFER, transformedSquare.size() * sizeof(Vector3), transformedSquare.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &tXSquareVAO);
    glGenBuffers(1, &tXSquareVBO);
    glBindVertexArray(tXSquareVAO);
    glBindBuffer(GL_ARRAY_BUFFER, tXSquareVBO);
    glBufferData(GL_ARRAY_BUFFER, transformedXSquare.size() * sizeof(Vector3), transformedXSquare.data(), GL_DYNAMIC_DRAW);
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

        glBindVertexArray(gridVAO);
        glUniform3f(uColorLoc, 1.0f, 1.0f, 1.0f);
        glUniform2f(uOffsetLoc, 0.0f, 0.0f);
        glUniform1f(uScaleLoc, 1.0f);
        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(grid.size()));

        glBindVertexArray(squareVAO);
        glUniform3f(uColorLoc, 0.0f, 1.0f, 1.0f);
        glUniform2f(uOffsetLoc, 0.0f, 0.0f);
        glUniform1f(uScaleLoc, 1.0f);
        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(square.size()));

        glBindVertexArray(tSquareVAO);
        glUniform3f(uColorLoc, 0.0f, 1.0f, 0.0f);
        glUniform2f(uOffsetLoc, 0.0f, 0.0f);
        glUniform1f(uScaleLoc, 1.0f);
        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(transformedSquare.size()));

        transformedXSquare.clear();
        Matrix4 rotation = Matrix4::makeRotationZ(toRadians(currentAngle++));
        Matrix4 transform = translation * rotation;
        for (auto &vect : square) {
            Vector4 vect4(vect.x, vect.y, vect.z, 1);
            auto transformed = transform * vect4;
            transformedXSquare.emplace_back(transformed.x, transformed.y, transformed.z);
        }

        glBindBuffer(GL_ARRAY_BUFFER, tXSquareVBO);
        glBufferData(GL_ARRAY_BUFFER, transformedXSquare.size() * sizeof(Vector3), transformedXSquare.data(), GL_DYNAMIC_DRAW);

        glBindVertexArray(tXSquareVAO);
        glUniform3f(uColorLoc, 1.0f, 0.0f, 0.0f);
        glUniform2f(uOffsetLoc, 0.0f, 0.0f);
        glUniform1f(uScaleLoc, 1.0f);
        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(transformedXSquare.size()));

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}