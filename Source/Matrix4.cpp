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

Vector4 Matrix4::operator*(const Vector4 &vector4) {
    Vector4 resultVector4;

    float sum = 0;
    for (int r = 0; r < row; r++) {
        sum = 0;
        for (int c = 0; c < col; c++) {
            if (c == 0) {
                sum += get(r, c) * vector4.x;
                continue;
            }
            if (c == 1) {
                sum += get(r, c) * vector4.y;
                continue;
            }
            if (c == 2) {
                sum += get(r, c) * vector4.z;
                continue;
            }
            if (c == 3) {
                sum += get(r, c) * vector4.w;
                continue;
            }
        }
        if (r == 0) {
            resultVector4.x = sum;
            continue;
        }
        if (r == 1) {
            resultVector4.y = sum;
            continue;
        }
        if (r == 2) {
            resultVector4.z = sum;
            continue;
        }
        if (r == 3) {
            resultVector4.w = sum;
            continue;
        }
    }

    return resultVector4;
}

Matrix4 Matrix4::makeTranslation(float x, float y, float z) {
    Matrix4 resultingMatrix;

    resultingMatrix.set(0,0, 1);
    resultingMatrix.set(1,1, 1);
    resultingMatrix.set(2,2, 1);
    resultingMatrix.set(3,3, 1);

    resultingMatrix.set(0,3, x);
    resultingMatrix.set(1,3, y);
    resultingMatrix.set(2,3, z);

    return resultingMatrix;
}

Matrix4 Matrix4::makeTranslation(const Vector3 &vector3) {
    Matrix4 resultingMatrix;

    resultingMatrix.set(0,0, 1);
    resultingMatrix.set(1,1, 1);
    resultingMatrix.set(2,2, 1);
    resultingMatrix.set(3,3, 1);

    resultingMatrix.set(0,3, vector3.x);
    resultingMatrix.set(1,3, vector3.y);
    resultingMatrix.set(2,3, vector3.z);

    return resultingMatrix;
}

Matrix4 Matrix4::makeRotationY(float angleRadians) {
    Matrix4 resultingMatrix;

    float sinVal = std::sinf(angleRadians);
    float cosVal = std::cosf(angleRadians);

    if (std::abs(sinVal) < 0.00001f) sinVal = 0.0f;
    if (std::abs(cosVal) < 0.00001f) cosVal = 0.0f;

    resultingMatrix.set(0, 0, cosVal);
    resultingMatrix.set(0, 2, sinVal);
    resultingMatrix.set(2, 0, -sinVal);
    resultingMatrix.set(2, 2, cosVal);
    resultingMatrix.set(1, 1, 1);
    resultingMatrix.set(3, 3, 1);

    return resultingMatrix;
}

Matrix4 Matrix4::makeRotationX(float angleRadians) {
    Matrix4 resultingMatrix;

    float sinVal = std::sinf(angleRadians);
    float cosVal = std::cosf(angleRadians);

    if (std::abs(sinVal) < 0.00001f) sinVal = 0.0f;
    if (std::abs(cosVal) < 0.00001f) cosVal = 0.0f;

    resultingMatrix.set(0, 0, 1);
    resultingMatrix.set(1, 1, cosVal);
    resultingMatrix.set(1, 2, -sinVal);
    resultingMatrix.set(2, 1, sinVal);
    resultingMatrix.set(2, 2, cosVal);
    resultingMatrix.set(3, 3, 1);

    return resultingMatrix;
}

Matrix4 Matrix4::makeRotationZ(float angleRadians) {
    Matrix4 resultingMatrix;

    float sinVal = std::sinf(angleRadians);
    float cosVal = std::cosf(angleRadians);

    if (std::abs(sinVal) < 0.00001f) sinVal = 0.0f;
    if (std::abs(cosVal) < 0.00001f) cosVal = 0.0f;

    resultingMatrix.set(0, 0, cosVal);
    resultingMatrix.set(1, 0, sinVal);
    resultingMatrix.set(0, 1, -sinVal);
    resultingMatrix.set(1, 1, cosVal);
    resultingMatrix.set(2, 2, 1);
    resultingMatrix.set(3, 3, 1);

    return resultingMatrix;
}

Matrix4 Matrix4::makePerspective(float fovY, float aspectRatio, float near, float far) {
    Matrix4 resultingMatrix;
    float focalLength = 1.0f / std::tanf(fovY / 2.0f);

    resultingMatrix.set(0, 0, focalLength / aspectRatio);
    resultingMatrix.set(1, 1, focalLength);
    resultingMatrix.set(2, 2, (far + near) / (near - far));
    resultingMatrix.set(2, 3, (2 * far * near) / (near - far));
    resultingMatrix.set(3, 2, -1);

    return resultingMatrix;
}

Matrix4 Matrix4::makeLookAt(Vector3 eye, Vector3 target, Vector3 worldUp) {
    Vector3 forward = eye - target;
    forward.normalize();

    Vector3 right = worldUp % forward;
    right.normalize();

    Vector3 up = forward % right;
}

void Matrix4::print() {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            std:: cout << get(r, c) << " ";
        }
        std:: cout << "\n";
    }
}
