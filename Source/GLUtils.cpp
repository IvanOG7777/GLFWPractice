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
