//
// Created by elder on 6/28/2026.
//

#ifndef GLFWPRACTICE_MATRIX4_H
#define GLFWPRACTICE_MATRIX4_H

#include <vector>

#include "Vector3.h"
#include "Vector4.h"

class Matrix4 {
    int col;
    int row;
    std::vector<std::vector<float>> data;

public:
    Matrix4();

    void set(int r, int c, float val);
    float get(int r, int c);

    const int getRow() const ;
    const int getCol() const ;

    Matrix4 operator*(Matrix4 &matrix);
    Vector4 operator*(const Vector4 &vector4);

    static Matrix4 makeTranslation(float x, float y, float z); // belongs to class and not a specific instance of Matrix object
    static Matrix4 makeTranslation(const Vector3 &vector3);

    static Matrix4 makeRotationY(float angleRadians);
    static Matrix4 makeRotationX(float angleRadians);

    void print();
};

#endif //GLFWPRACTICE_MATRIX4_H