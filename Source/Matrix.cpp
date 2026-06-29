//
// Created by elder on 6/28/2026.
//

#include "../Header/Matrix.h"
#include <iostream>

Matrix::Matrix() {
    row = 4;
    col = 4;
    data.resize(col, std::vector<float>(row));

}


Matrix::Matrix(int passedRow, int passedCol) {
    row = passedRow;
    col = passedCol;
    data.resize(col, std::vector<float>(row));
}

void Matrix::set(int r, int c, float val) {
    data[c][r] = val;
}

float Matrix::get(int r, int c) {
    return data[c][r];
}

const int Matrix::getRow() const {
    return row;
}

const int Matrix::getCol() const {
    return col;
}

Matrix Matrix::operator*(Matrix &matrix) {
    if (col != matrix.row) {
        std:: cerr << "BAD MULTIPLICATION, ROW AND COL DO NOT MATCH" << std:: endl;
        exit(EXIT_FAILURE);
    }

    Matrix resultingMatrix(row, matrix.col);
    float resultingValue = 0;

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < matrix.col; c++) {
            resultingValue = 0;
            for (int k = 0; k < col; k++) {
                float aVal = get(r, k);
                float bVal = matrix.get(k, c);
                float newValue = aVal * bVal;
                resultingValue += newValue;
            }
            resultingMatrix.set(r, c, resultingValue);
        }
    }

    return resultingMatrix;
}

void Matrix::print() {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            std:: cout << get(r, c) << " ";
        }
        std:: cout << "\n";
    }
}
