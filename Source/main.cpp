//
// Created by elder on 6/26/2026.
//

#include <iostream>
#include <random>
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
#include "../Header/Sphere.h"


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

    SphereParticle blackhole;
    std::vector<glm::vec3> sphere = makeSphere(1.0f); //
    blackhole.setMesh(sphere);
    blackhole.setPosition(0.0f, 0.0f, 0.0f);
    blackhole.setTrailPosition(blackhole.getPosition());

    std:: vector<std::vector<glm::vec3>> spheres;

    std:: vector<SphereParticle> sphere_particles;
    sphere_particles.resize(5);

    float radius = 1.0f;
    for (int i = 0; i < 5; i++) {

        int min = 10;
        int max = 50;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        int randVal = distrib(gen);

        auto mesh = makeSphere(radius * 1.5f);
        sphere_particles[i].setMesh(mesh);
        sphere_particles[i].setPosition(static_cast<float>(randVal), static_cast<float>(randVal - 5), static_cast<float>(randVal + 20));
        sphere_particles[i].setTrailPosition(sphere_particles[i].getPosition());
    }

    glm::mat4 translationSphere = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f)); // translates to world space


    int sphereIndex = 0;

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), W/H, 0.1f, 1000.0f);

    glm::mat4 view = camera.getViewMatrix();

    glm::mat4 lookAtMatrix = glm::lookAt(camera.getPosition(), {0.0f,0.0f,0.0f}, {0.0f, 1.0f, 0.0f});

    glm::mat4 sphereMVP;
    glm::mat4 trailMVP;
    glm::vec3 acceleration = {5.0f, 5.0f, 5.0f};
    glm::vec3 velocity = {20.0f, 5.0f, 2.0f};

    sceneState.camera = &camera;

    glm::vec3 sphereCenter = blackhole.getPosition();
    radius = 50.0f;


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

    GLuint sphereVAO = 0, trailVAO = 0;
    GLuint sphereVBO = 0, trailVBO = 0;

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

    GLuint uColorLoc = glGetUniformLocation(threeDProgram, "uColor");
    GLuint uMVP = glGetUniformLocation(threeDProgram, "uMVP");

    glGenVertexArrays(1, &sphereVAO);
    glGenBuffers(1, &sphereVBO);
    glBindVertexArray(sphereVAO);
    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    glBufferData(GL_ARRAY_BUFFER, blackhole.getMeshSize() * sizeof(glm::vec3), blackhole.getMeshData(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &trailVAO);
    glGenBuffers(1, &trailVBO);
    glBindVertexArray(trailVAO);
    glBindBuffer(GL_ARRAY_BUFFER, trailVBO);
    glBufferData(GL_ARRAY_BUFFER, blackhole.getTrailSize() * sizeof(ParticleTrail), blackhole.getTrailData(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleTrail), (void*)0);
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

        sphereMVP = projection * view * translationSphere;
        trailMVP = projection * view * glm::mat4(1.0f);

        velocity += acceleration;
        velocity *= deltaTime * 0.1;

        glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
        glBufferData(GL_ARRAY_BUFFER, blackhole.getMeshSize() * sizeof(glm::vec3), blackhole.getMeshData(), GL_DYNAMIC_DRAW);
        glUniformMatrix4fv(uMVP, 1, GL_FALSE, glm::value_ptr(sphereMVP));
        glBindVertexArray(sphereVAO);
        glUniform3f(uColorLoc, 1.0f, 0.2f, 0.4f);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(blackhole.getMeshSize()));

        sphereIndex = 0;
        for (auto &sphereI : sphere_particles) {

            auto currentPosition = sphereI.getPosition();

            currentPosition += velocity;

            auto x = sphereCenter.x + (radius * std:: cosf(currentPosition.x));
            auto y = (radius * std:: cosf(currentPosition.x)) + (sphereCenter.z + (radius * std:: sinf(currentPosition.z)));
            auto z = sphereCenter.z + (radius * std:: sinf(currentPosition.z));

            glm::vec3 pt = {x, y, z};

            sphereI.setPosition(pt);

            ParticleTrail currentTrailPosition;
            currentTrailPosition.positon = pt;

            sphereI.setTrailPosition(currentTrailPosition);
            sphereIndex++;
        }

        sphereIndex = 0;
        for (auto &sphereI : sphere_particles) {
            // rebinds the sphere and trail VBOS
            glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
            glBufferData(GL_ARRAY_BUFFER, sphereI.getMeshSize() * sizeof(glm::vec3), sphereI.getMeshData(), GL_DYNAMIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, trailVBO);
            glBufferData(GL_ARRAY_BUFFER, sphereI.getTrailSize() * sizeof(ParticleTrail), sphereI.getTrailData(), GL_DYNAMIC_DRAW);

            sphereMVP = projection * view * glm::translate(glm::mat4(1.0f), sphereI.getPosition());

            // paints the spheres
            glUniformMatrix4fv(uMVP, 1, GL_FALSE, glm::value_ptr(sphereMVP));
            glBindVertexArray(sphereVAO);
            if (sphereIndex == 0) glUniform3f(uColorLoc, 1.0f, 0.0f, 0.0f);
            if (sphereIndex == 1) glUniform3f(uColorLoc, 0.0f, 1.0f, 0.0f);
            if (sphereIndex == 2) glUniform3f(uColorLoc, 0.0f, 0.0f, 1.0f);
            if (sphereIndex == 3) glUniform3f(uColorLoc, 1.0f, 1.0f, 0.0f);
            if (sphereIndex == 4) glUniform3f(uColorLoc, 1.0f, 1.0f, 1.0f);
            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(sphereI.getMeshSize()));

            // paints the trails
            glUniformMatrix4fv(uMVP, 1, GL_FALSE, glm::value_ptr(trailMVP));
            glBindVertexArray(trailVAO);
            if (sphereIndex == 0) glUniform3f(uColorLoc, 1.0f, 0.0f, 0.0f);
            if (sphereIndex == 1) glUniform3f(uColorLoc, 0.0f, 1.0f, 0.0f);
            if (sphereIndex == 2) glUniform3f(uColorLoc, 0.0f, 0.0f, 1.0f);
            if (sphereIndex == 3) glUniform3f(uColorLoc, 1.0f, 1.0f, 0.0f);
            if (sphereIndex == 4) glUniform3f(uColorLoc, 1.0f, 1.0f, 1.0f);
            glDrawArrays(GL_LINE_STRIP, 0, static_cast<GLsizei>(sphereI.getTrailSize()));

            sphereIndex++;
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

//TODO make photon sphere and other sphere around black hole for particles to orbit