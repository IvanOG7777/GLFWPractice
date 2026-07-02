//
// Created by elder on 6/30/2026.
//

#ifndef GLFWPRACTICE_CAMERA_H
#define GLFWPRACTICE_CAMERA_H

#include <glm/glm/glm.hpp>
#include "GLFW/glfw3.h"

class Camera {
private:
    glm::vec3 position;
    glm::vec3 worldUp;
    float yaw; // left and right (horizontal) rotation
    float pitch; // up and down (vertical) rotation
public:
    float currentYaw;
    float currentPitch;
    float currentX;
    float currentY;
    float currentZ;

public:
    Camera();

    glm::vec3 getDirection() const;

    glm::vec3 getRight();

    glm::mat4 getViewMatrix();

    void setPosition(glm::vec3 &passedPosition);
    void setPosition(float passedX,float passedY, float passedZ);
    void setYaw(float yawRadians);
    void setPitch(float pitchRadians);

    glm::vec3 &getPosition();
    float &getYaw();
    float &getPitch();

    void move(GLFWwindow *window, float deltaTime);

};

#endif //GLFWPRACTICE_CAMERA_H