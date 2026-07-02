//
// Created by elder on 6/26/2026.
//

#ifndef GLWFPRACTICE_GLUTILS_H
#define GLWFPRACTICE_GLUTILS_H

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "Camera.h"

struct SceneState {
    Camera *camera;
};

GLFWwindow *createWindow();

void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

#endif //GLWFPRACTICE_GLUTILS_H