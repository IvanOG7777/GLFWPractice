//
// Created by elder on 6/28/2026.
//

#include "../Header/Vector3.h"

Vector3::Vector3() {
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float passedX, float passedY, float passedZ) {
    x = passedX;
    y = passedY;
    z = passedZ;
}

void Vector3::setVector3(Vector3 vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
}

void Vector3::setVector3(float passedX, float passedY, float passedZ) {
    x = passedX;
    y = passedY;
    z = passedZ;
}
//Cross product
Vector3 Vector3::operator%(Vector3 &vector) const {
    float newX = (y * vector.z) - (z * vector.y);
    float newY = (z * vector.x) - (x * vector.z);
    float newZ = (x * vector.y) - (y * vector.x);

    return {newX, newY, newZ};
}

Vector3 Vector3::operator-(Vector3 &vector) const {
    float newX = x - vector.x;
    float newY = y - vector.y;
    float newZ = z - vector.z;

    return {newX, newY, newZ};
}

Vector3 Vector3::operator+(Vector3 &vector) const {
    float newX = x + vector.x;
    float newY = y + vector.y;
    float newZ = z + vector.z;

    return {newX, newY, newZ};
}

float Vector3::magnitude() {
    return std::sqrtf(x*x + y*y + z*z);
}

float Vector3::magnitudeSquared() {
    return x*x + y*y + z*z;
}

void Vector3::normalize() {
    float length = magnitude();
    if (length > 0.0f) {
        x /= length;
        y /= length;
        z /= length;
    }
}

float Vector3::scalarProduct(const Vector3 &vector) const {
    return (x * vector.x) + (y * vector.y) + (z * vector.z);
}

std::ostream &operator<<(std::ostream &stream, const Vector3 &vector) {
    stream << "x: " << vector.x << ", y: " << vector.y << ", z: " <<vector.z;
    return stream;
}