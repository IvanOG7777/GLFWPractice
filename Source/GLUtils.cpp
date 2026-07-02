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

    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        camera->setPosition(camera->getPosition().x , camera->getPosition().z, camera->currentZ++);
    }

    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        camera->setPosition(camera->cux-- , camera->getPosition().z, camera->currentZ--);
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        camera->setPosition(camera->getPosition().x , camera->getPosition().z, camera->currentZ--);
    }

    if (key == GLFW_KEY_D && action == GLFW_PRESS) {

    }
}
