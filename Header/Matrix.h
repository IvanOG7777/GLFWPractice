//
// Created by elder on 6/28/2026.
//

#ifndef GLFWPRACTICE_MATRIX4_H
#define GLFWPRACTICE_MATRIX4_H

#include <vector>

#include "Vector3.h"

class Matrix {
    int col;
    int row;
    std::vector<std::vector<float>> data;

public:
    Matrix();
    Matrix(int passedRow, int passedCol);

    void set(int r, int c, float val);
    float get(int r, int c);

    const int getRow() const ;
    const int getCol() const ;

    Matrix operator*(Matrix &matrix);

    Matrix makeTranslation(float x, float y, float z);
    Matrix makeTranslation(Vector3);

    void print();
};

#endif //GLFWPRACTICE_MATRIX4_H