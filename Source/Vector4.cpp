//
// Created by elder on 6/29/2026.
//

#include "../Header/Vector4.h"

Vector4::Vector4() {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

Vector4::Vector4(float passedX, float passedY, float passedZ, float passedW) {
    x = passedX;
    y = passedY;
    z = passedZ;
    w = passedW;
}

void Vector4::setVector4(float passedX, float passedY, float passedZ, float passedW) {
    x = passedX;
    y = passedY;
    z = passedZ;
    w = passedW;
}

void Vector4::setVector4(const Vector4 &vector4) {
    x = vector4.x;
    y = vector4.y;
    z = vector4.z;
    w = vector4.w;
}

float Vector4::magnitude() {
    return std::sqrtf(x*x + y*y + z*z + w*w);
}

float Vector4::magnitudeSquared() {
    return x*x + y*y + z*z + w*w;
}

void Vector4::normalize() {
    float length = magnitude();
    if (length > 0.0f) {
        x /= length;
        y /= length;
        z /= length;
        w /= length;
    }
}

float Vector4::scalarProduct(const Vector4 &vector4) const {
    return (x * vector4.x) + (y * vector4.y) + (z * vector4.z) + (w * vector4.w);
}
