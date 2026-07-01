//
// Created by elder on 6/30/2026.
//

#ifndef GLFWPRACTICE_CAMERA_H
#define GLFWPRACTICE_CAMERA_H

#include "Matrix4.h"

class Camera {
private:
    Vector3 position;
    Vector3 worldUp;
    float yaw; // left and right (horizontal) rotation
    float pitch; // up and down (vertical) rotation

public:
    Camera();

    Vector3 getDirection() const;

    Vector3 getRight();

    Matrix4 getViewMatrix();

    void setPosition(Vector3 &passedPosition);
    void setYaw(float yawRadians);
    void setPitch(float pitchRadians);

    Vector3 &getPosition();
    float &getYaw();
    float &getPitch();

};

#endif //GLFWPRACTICE_CAMERA_H