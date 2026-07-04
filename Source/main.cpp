//
// Created by elder on 6/26/2026.
//

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "../Header/Camera.h"
#include "../Header/GLUtils.h"
#include "../Header/Geometry.h"
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

    SceneState sceneState {};
    Camera camera;

    camera.setPosition(0, 1.5f, 10);

    std::vector<glm::vec3> grid = makeGrid(4);
    std::vector<glm::vec3> square = makeSquare(); // creates square in its own local space
    std::vector<glm::vec3> cube = makeCube();
    std::vector<glm::vec3> sphere = makeSphere(5);
    std:: vector<std::vector<glm::vec3>> spheres;
    std::vector<glm::vec3> grid3D = makeGrid2DVertical(100, 100, 10, 10);
    // std::vector<glm::vec3> grid2D = makeGrid2D();

    float radius = 1.0f;
    for (int i = 0; i < 5; i++) {
        auto sphereL = makeSphere(radius * 1.5f);
        radius *= 1.5f;
        spheres.emplace_back(sphereL);
    }

    glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(-20.f, 0.0f, -50.0f));
    glm::mat4 translationCube = glm::translate(glm::mat4(1.0f), glm::vec3(12.0f, 4.0f, 5.0f)); // translates to world space
    glm::mat4 translationSphere = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f)); // translates to world space
    glm::mat4 translation1 = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 0.0f)); // translates to world space
    glm::mat4 translation2 = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, -10.0f, 0.0f)); // translates to world space
    glm::mat4 translation3 = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 10.0f, -10.0f)); // translates to world space
    glm::mat4 translation4 = glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, 0.0f, 0.0f)); // translates to world space
    glm::mat4 translation5 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 20.0f, -15.0f)); // translates to world space
    glm::mat4 originTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    std:: vector<glm::mat4> translations;
    translations.emplace_back(translation1);
    translations.emplace_back(translation2);
    translations.emplace_back(translation3);
    translations.emplace_back(translation4);
    translations.emplace_back(translation5);
    int sphereIndex = 0;

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), W/H, 0.1f, 1000.0f);

    glm::mat4 view = camera.getViewMatrix();

    glm::mat4 lookAtMatrix = glm::lookAt(camera.getPosition(), {0.0f,0.0f,0.0f}, {0.0f, 1.0f, 0.0f});

    glm::mat4 MVP;
    glm::mat4 cubeMVP;
    glm::mat4 sphereMVP;
    glm::mat4 gridMVP;

    sceneState.camera = &camera;



    GLFWwindow *window = createWindow();
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "GLAD INIT ERROR\n";
        return -1;
    }

    glfwSetWindowUserPointer(window, &sceneState);

    glfwSetKeyCallback(window, keyboardCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    GLuint gridVAO = 0, squareVAO = 0, cubeVAO = 0, sphereVAO = 0;
    GLuint gridVBO = 0, squareVBO = 0, cubeVBO = 0, sphereVBO = 0;

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
    glBufferData(GL_ARRAY_BUFFER, grid3D.size() * sizeof(glm::vec3), grid3D.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &squareVAO);
    glGenBuffers(1, &squareVBO);
    glBindVertexArray(squareVAO);
    glBindBuffer(GL_ARRAY_BUFFER, squareVBO);
    glBufferData(GL_ARRAY_BUFFER, square.size() * sizeof(glm::vec3), square.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, cube.size() * sizeof(glm::vec3), cube.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &sphereVAO);
    glGenBuffers(1, &sphereVBO);
    glBindVertexArray(sphereVAO);
    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    glBufferData(GL_ARRAY_BUFFER, sphere.size() * sizeof(glm::vec3), sphere.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);

    auto startTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        auto currentTime = glfwGetTime();
        auto deltaTime = currentTime - startTime;
        startTime = currentTime;
        camera.cameraSpeed = 10.0f;
        int w = W;
        int h = H;
        glfwGetFramebufferSize(window, &w, &h);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int wKey = glfwGetKey(window, GLFW_KEY_W);
        int aKey = glfwGetKey(window, GLFW_KEY_A);
        int sKey = glfwGetKey(window, GLFW_KEY_S);
        int dKey = glfwGetKey(window, GLFW_KEY_D);
        int spaceKey = glfwGetKey(window, GLFW_KEY_SPACE);
        int leftControlKey = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL);
        int leftShift = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);

        camera.cameraSpeed *= static_cast<float>(deltaTime);
        glm::vec3 position = camera.getPosition();
        glm::vec3 direction = camera.getDirection();
        glm::vec3 right = camera.getRight();

        // keyboard polling
        if (wKey == GLFW_PRESS) {
            position += direction * camera.cameraSpeed;
        }
        if (sKey == GLFW_PRESS) {
            position -= direction * camera.cameraSpeed;
        }
        if (dKey == GLFW_PRESS) {
            position += right * camera.cameraSpeed;
        }
        if (aKey== GLFW_PRESS) {
            position -= right * camera.cameraSpeed;
        }
        if (spaceKey == GLFW_PRESS) {
            position.y += camera.cameraSpeed;
        }
        if (leftControlKey == GLFW_PRESS) {
            position.y -= camera.cameraSpeed;
        }

        if (wKey == GLFW_PRESS && leftShift == GLFW_PRESS) {
            position += direction *  (camera.cameraSpeed * 2);
        }
        if (sKey == GLFW_PRESS && leftShift == GLFW_PRESS) {
            position -= direction *  (camera.cameraSpeed * 2);
        }
        if (dKey == GLFW_PRESS && leftShift == GLFW_PRESS) {
            position += right *  (camera.cameraSpeed * 2);
        }
        if (aKey== GLFW_PRESS && leftShift == GLFW_PRESS) {
            position -= right * (camera.cameraSpeed * 2);
        }
        if (spaceKey == GLFW_PRESS && leftShift == GLFW_PRESS) {
            position.y += camera.cameraSpeed * 2;
        }
        if (leftControlKey == GLFW_PRESS && leftShift == GLFW_PRESS) {
            position.y -= camera.cameraSpeed * 2;
        }
        // keyboard polling

        camera.setPosition(position);

        glUseProgram(threeDProgram);

        view = camera.getViewMatrix();

        cubeMVP = projection * view * translationCube;
        MVP = projection * view * translation;
        sphereMVP = projection * view * translationSphere;
        gridMVP = projection * view * originTranslation;

        glUniformMatrix4fv(uMVP, 1, GL_FALSE, glm::value_ptr(MVP));
        glBindVertexArray(squareVAO);
        glUniform3f(uColorLoc, 0.0f, 1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(square.size()));


        glUniformMatrix4fv(uMVP, 1, GL_FALSE, glm::value_ptr(cubeMVP));
        glBindVertexArray(cubeVAO);
        glUniform3f(uColorLoc, 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(cube.size()));

        glUniformMatrix4fv(uMVP, 1, GL_FALSE, glm::value_ptr(sphereMVP));
        glBindVertexArray(sphereVAO);
        glUniform3f(uColorLoc, 1.0f, 0.0f, 0.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(sphere.size()));

        sphereIndex = 0;
        for (auto &sphereI : spheres) {
            glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
            glBufferData(GL_ARRAY_BUFFER, sphereI.size() * sizeof(glm::vec3), sphereI.data(), GL_DYNAMIC_DRAW);

            sphereMVP = projection * view * translations[sphereIndex];
            glUniformMatrix4fv(uMVP, 1, GL_FALSE, glm::value_ptr(sphereMVP));
            glBindVertexArray(sphereVAO);
            if (sphereIndex == 0) glUniform3f(uColorLoc, 1.0f, 0.0f, 0.0f);
            if (sphereIndex == 1) glUniform3f(uColorLoc, 0.0f, 1.0f, 0.0f);
            if (sphereIndex == 2) glUniform3f(uColorLoc, 0.0f, 0.0f, 1.0f);
            if (sphereIndex == 3) glUniform3f(uColorLoc, 1.0f, 1.0f, 0.0f);
            if (sphereIndex == 4) glUniform3f(uColorLoc, 1.0f, 1.0f, 1.0f);
            glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(sphereI.size()));
            sphereIndex++;
        }

        glUniformMatrix4fv(uMVP, 1, GL_FALSE, glm::value_ptr(gridMVP));
        glBindVertexArray(gridVAO);
        glUniform3f(uColorLoc, 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(grid3D.size()));


        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

//TODO make photon sphere and other sphere around black hole for particles to orbit