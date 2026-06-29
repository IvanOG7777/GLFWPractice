//
// Created by elder on 6/28/2026.
//

#ifndef GLFWPRACTICE_MATRIX4_H
#define GLFWPRACTICE_MATRIX4_H

#include <vector>

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

    Vector4 makeTranslation(float x, float y, float z, float w);
    Vector4 makeTranslation(const Vector4 &vector4);

    void print();
};

#endif //GLFWPRACTICE_MATRIX4_H