//
// Created by elder on 6/28/2026.
//

#include "../Header/Matrix4.h"
#include <iostream>

Matrix4::Matrix4() {
    row = 4;
    col = 4;
    data.resize(col, std::vector<float>(row));

}

void Matrix4::set(int r, int c, float val) {
    data[c][r] = val;
}

float Matrix4::get(int r, int c) {
    return data[c][r];
}

const int Matrix4::getRow() const {
    return row;
}

const int Matrix4::getCol() const {
    return col;
}

Matrix4 Matrix4::operator*(Matrix4 &matrix) {
    if (col != matrix.row) {
        std:: cerr << "BAD MULTIPLICATION, ROW AND COL DO NOT MATCH" << std:: endl;
        exit(EXIT_FAILURE);
    }

    Matrix4 resultingMatrix;
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

Vector4 Matrix4::makeTranslation(float x, float y, float z, float w) {
    Vector4 resultingVector4;

    float sum = 0;
    for (int r = 0; r < row; r++) {
        sum = 0;
        for (int c = 0; c < col; c++) {
            if (c == 0) {
                sum += get(r, c) * x;
                continue;
            }
            if (c == 1) {
                sum += get(r, c) * y;
                continue;
            }
            if (c == 2) {
                sum += get(r, c) * z;
                continue;
            }
            if (c == 3) {
                sum += get(r, c) * w;
                continue;
            }
        }
        if (r == 0) {
            resultingVector4.x = sum;
            continue;
        }
        if (r == 1) {
            resultingVector4.y = sum;
            continue;
        }
        if (r == 2) {
            resultingVector4.z = sum;
            continue;
        }
        if (r == 3) {
            resultingVector4.w = sum;
            continue;
        }
    }
    return resultingVector4;
}

void Matrix4::print() {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            std:: cout << get(r, c) << " ";
        }
        std:: cout << "\n";
    }
}
