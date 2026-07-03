//
// Created by elder on 6/30/2026.
//

#include "../Header/Camera.h"

#include "glm/glm/gtc/matrix_transform.hpp"

Camera::Camera() {
    position = {0.0f,0.0f,0.0f};
    worldUp = {0, 1, 0};
    // both must be in radians
    yaw = 0.0f; // left and right (horizontal) rotation
    pitch = 0.0f; // up and down (vertical) rotation
    currentYaw = 0.0f;
    currentPitch = 0.0f;
    cameraSpeed = 15.0f;
    firstMove = true;
}

// a normalized vector as to where the camera points at in space
glm::vec3 Camera::getDirection() const {
    float x = std::cosf(pitch) * std:: sinf(yaw);
    float y = std::sinf(pitch);
    float z = -std::cosf(pitch) * std:: cosf(yaw);

    glm::vec3 direction(x, y, z);

    direction = glm::normalize(direction);

    return direction;
}

glm::vec3 Camera::getRight() {
    glm::vec3 direction = getDirection();
    glm::vec3 right = glm::cross(direction, worldUp);

    right = glm::normalize(right);

    return right;
}

glm::mat4 Camera::getViewMatrix() {
    auto direction = getDirection();
    auto target = position + direction;
    glm::mat4 resultingMatrix = glm::lookAt(position, target, worldUp);

    return resultingMatrix;
}

void Camera::setPosition(glm::vec3 &passedPosition) {
    position.x = passedPosition.x;
    position.y = passedPosition.y;
    position.z = passedPosition.z;
}

void Camera::setPosition(float passedX, float passedY, float passedZ) {
    position.x = passedX;
    position.y = passedY;
    position.z = passedZ;
}

void Camera::setYaw(float yawRadians) {
    yaw = yawRadians;
}

void Camera::setPitch(float pitchRadians) {
    pitch = pitchRadians;
}

glm::vec3 &Camera::getPosition() {
    return position;
}

float &Camera::getYaw() {
    return yaw;
}

float &Camera::getPitch() {
    return pitch;
}
