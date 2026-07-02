//
// Created by elder on 6/30/2026.
//

#include "../Header/Camera.h"

Camera::Camera() {
    position = {0.0f,0.0f,0.0f};
    worldUp = {0, 1, 0};
    // both must be in radians
    yaw = 0.0f; // left and right (horizontal) rotation
    pitch = 0.0f; // up and down (vertical) rotation
}

// a normalized vector as to where the camera points at in space
Vector3 Camera::getDirection() const {
    float x = std::cosf(pitch) * std:: sinf(yaw);
    float y = std::sinf(pitch);
    float z = -std::cosf(pitch) * std:: cosf(yaw);

    Vector3 direction(x, y, z);

    direction.normalize();

    return direction;
}

Vector3 Camera::getRight() {
    Vector3 direction = getDirection();
    Vector3 right = direction % worldUp;

    right.normalize();

    return right;
}

Matrix4 Camera::getViewMatrix() {
    auto direction = getDirection();
    auto target = position + direction;
    std:: cout << "Direction: " << direction << std:: endl;
    std:: cout << "Target: " << target << std:: endl;
    Matrix4 resultingMatrix = Matrix4::makeLookAt(position, target, worldUp);

    return resultingMatrix;
}

void Camera::setPosition(Vector3 &passedPosition) {
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

Vector3 &Camera::getPosition() {
    return position;
}

float &Camera::getYaw() {
    return yaw;
}

float &Camera::getPitch() {
    return pitch;
}

void Camera::move(GLFWwindow *window, float deltaTime) {
    
}
