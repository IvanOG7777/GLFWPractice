//
// Created by elder on 6/26/2026.
//

#include <iostream>
#include "../Header/GLUtils.h"

#include <iostream>

//TODO automatically get users window size and set to full screen
GLFWwindow *createWindow() {
    GLFWwindow *window = glfwCreateWindow(1920, 1080, "GLFW Practice", nullptr, nullptr);

    if (window == nullptr) {
        std:: cerr << "BAD WINDOW, WINDOW IS NULLPTR" << std:: endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return window;
}

void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto *state = static_cast<SceneState*>(glfwGetWindowUserPointer(window));
    auto *camera = state->camera;
    glm::vec3 position = camera->getPosition();
    float speed = camera->cameraSpeed;

    if (key == GLFW_KEY_W && action == GLFW_REPEAT) {
        position.z -= speed;
        std:: cout << "Moved forward" << std:: endl;
    }

    if (key == GLFW_KEY_S && action == GLFW_REPEAT) {
        position.z += speed;
        std:: cout << "Moved backward" << std:: endl;
    }

    if (key == GLFW_KEY_A && action == GLFW_REPEAT) {
        position.x -= speed;
        std:: cout << "Moved left" << std:: endl;
    }

    if (key == GLFW_KEY_D && action == GLFW_REPEAT) {
        position.x += speed;
        std:: cout << "Moved right" << std:: endl;
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_REPEAT) {
        position.y += speed;
        std:: cout << "Moving up" << std:: endl;
    }

    if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_REPEAT) {
        position.y -= speed;
        std:: cout << "Moving down" << std:: endl;
    }

    camera->setPosition(position);
}

void cursorPositionCallback(GLFWwindow *window, double positionX, double positionY) {
    auto *state = static_cast<SceneState*>(glfwGetWindowUserPointer(window));
    auto *camera = state->camera;

    //
    if (camera->firstMove == true) {
        camera->currentX = positionX;
        camera->currentY = positionY;
        camera->firstMove = false;
        return;
    }

    float deltaX = camera->currentX - static_cast<float>(positionX);
    float deltaY = camera->currentY - static_cast<float>(positionY);

    float pitch = camera->getPitch();
    float yaw = camera->getYaw();

    yaw -= deltaX * 0.001f;
    pitch += deltaY * 0.001f;

    camera->setYaw(yaw);
    camera->setPitch(pitch);

    camera->currentX = positionX;
    camera->currentY = positionY;

}
