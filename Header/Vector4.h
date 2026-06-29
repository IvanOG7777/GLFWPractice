//
// Created by elder on 6/29/2026.
//

#ifndef GLFWPRACTICE_VECTOR4_H
#define GLFWPRACTICE_VECTOR4_H

#include <iostream>
class Vector4 {
public:
    float x;
    float y;
    float z;
    float w;

public:
    Vector4();

    Vector4(float passedX, float passedY, float passedZ, float passedW);

    void setVector4(const Vector4 &vector4);
    void setVector4(float passedX, float passedY, float passedZ, float passedW);

    float magnitude();
    float magnitudeSquared();
    void normalize();

    float scalarProduct(const Vector4 &vector4) const;

    friend std:: ostream &operator<<(std:: ostream &stream, const Vector4 &vector);
};

#endif //GLFWPRACTICE_VECTOR4_H