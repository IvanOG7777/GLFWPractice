//
// Created by elder on 6/27/2026.
//

#ifndef GLFWPRACTICE_VECTOR3_H
#define GLFWPRACTICE_VECTOR3_H

#include <iostream>

struct Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3();

    Vector3(float passedX, float passedY, float passedZ);
    void setVector3(Vector3 vector);
    void setVector3(float passedX, float passedY, float passedZ);

    friend std::ostream &operator<<(std::ostream &stream, const Vector3 &vector);
};

#endif //GLFWPRACTICE_VECTOR3_H