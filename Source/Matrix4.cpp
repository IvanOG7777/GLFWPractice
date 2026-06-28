//
// Created by elder on 6/28/2026.
//

#include "../Header/Matrix4.h"
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

void Matrix::print() {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            std:: cout << get(r, c) << " ";
        }
        std:: cout << "\n";
    }
}
