//
// Created by elder on 6/30/2026.
//

#ifndef GLFWPRACTICE_CAMERA_H
#define GLFWPRACTICE_CAMERA_H

#include "Matrix4.h"

class Camera {
private:
    Vector3 position;
    float yaw;
    float pitch;

public:
    Camera();

    Vector3 getDirection();

    Vector3 getRight();

    Matrix4 getViewMatrix();

};

#endif //GLFWPRACTICE_CAMERA_H