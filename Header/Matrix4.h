//
// Created by elder on 6/28/2026.
//

#ifndef GLFWPRACTICE_MATRIX4_H
#define GLFWPRACTICE_MATRIX4_H

#include <vector>

class Matrix {
    int col;
    int row;
    std::vector<std::vector<float>> data;

    Matrix();
    Matrix(int row, int col);

    void set(int row, int col, float val);
    void get(int row, int col);

    void print();
};

#endif //GLFWPRACTICE_MATRIX4_H