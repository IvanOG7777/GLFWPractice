//
// Created by elder on 6/26/2026.
//

#include <iostream>
#include <vector>

#include "../Header/Camera.h"
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

const char* threeDVSShader = R"GLSL(
    #version 330 core
    layout(location = 0) in vec3 aPos;

    uniform mat4 uMVP;

    void main() {
        gl_Position = uMVP * vec4(aPos, 1.0);
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

    Camera camera;
    camera.setPitch(toRadians(45));
    std:: cout << camera.getDirection() << std:: endl;
    return 0;

    std::vector<Vector3> grid = makeGrid(4);
    std::vector<Vector3> square = makeSquare(); // creates square in its own local space
    std::vector<Vector3> cube = makeCube();

    Matrix4 translation = Matrix4::makeTranslation(-20, 0, -50);
    Matrix4 translation2 = Matrix4::makeTranslation(0, 0, 0);

    Matrix4 projection = Matrix4:: makePerspective(toRadians(45), W/H, 0.1, 1000);

    Matrix4 view = Matrix4::makeLookAt({5, 8, 10}, {0, 0, 0}, {0, 1, 0});

    Matrix4 MVP = projection * view * translation;
    Matrix4 cubeMVP = projection * view * translation2;



    GLfloat matrix[16]; // stores the points in flatted array in row major order
    GLfloat cubeMatrix[16];
    int index = 0;
    for (int r = 0; r < MVP.getRow(); r++) {
        for (int c = 0; c < MVP.getCol(); c++) {
            float val = MVP.get(r, c);
            matrix[index++] = val;
        }
    }

    index = 0;
    for (int r = 0; r < cubeMVP.getRow(); r++) {
        for (int c = 0; c < cubeMVP.getCol(); c++) {
            float val = cubeMVP.get(r, c);
            cubeMatrix[index++] = val;
        }
    }


    GLFWwindow *window = createWindow();
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "GLAD INIT ERROR\n";
        return -1;
    }

    GLuint gridVAO = 0, squareVAO = 0, cubeVAO = 0;
    GLuint gridVBO = 0, squareVBO = 0, cubeVBO = 0;

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

    GLuint threeDvs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(threeDvs, 1, &threeDVSShader, nullptr);
    glCompileShader(threeDvs);

    GLuint threeDfs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(threeDfs, 1, &fragmentShader, nullptr);
    glCompileShader(threeDfs);

    GLuint threeDProgram = glCreateProgram();
    glAttachShader(threeDProgram, threeDvs);
    glAttachShader(threeDProgram, threeDfs);
    glLinkProgram(threeDProgram);

    glDeleteShader(threeDvs);
    glDeleteShader(threeDfs);

    GLuint uResolutionLoc = glGetUniformLocation(shaderProgram, "uResolution");
    GLuint uColorLoc = glGetUniformLocation(threeDProgram, "uColor");
    GLuint uOffsetLoc = glGetUniformLocation(shaderProgram, "uOffset");
    GLuint uScaleLoc = glGetUniformLocation(shaderProgram, "uScale");
    GLuint uMVP = glGetUniformLocation(threeDProgram, "uMVP");

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

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, cube.size() * sizeof(Vector3), cube.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        int w = W;
        int h = H;
        glfwGetFramebufferSize(window, &w, &h);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(threeDProgram);

        glUniformMatrix4fv(uMVP, 1, GL_TRUE, matrix);

        glBindVertexArray(squareVAO);
        glUniform3f(uColorLoc, 0.0f, 1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(square.size()));

        glUniformMatrix4fv(uMVP, 1, GL_TRUE, cubeMatrix);

        glBindVertexArray(cubeVAO);
        glUniform3f(uColorLoc, 1.0f, 0.0f, 0.0f);
        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(cube.size()));



        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}