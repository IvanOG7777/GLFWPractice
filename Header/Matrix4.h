//
// Created by elder on 6/28/2026.
//

#ifndef GLFWPRACTICE_MATRIX4_H
#define GLFWPRACTICE_MATRIX4_H

#include <vector>

#include "Vector3.h"

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

    Matrix4 makeTranslation(float x, float y, float z);
    Matrix4 makeTranslation(Vector3);

    void print();
};

#endif //GLFWPRACTICE_MATRIX4_H