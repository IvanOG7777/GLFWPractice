//
// Created by elder on 6/27/2026.
//

#include "../Header/Geometry.h"

std::vector<Vector3> makeGrid(int slices) {
    std:: vector<Vector3> points;
    std:: vector<Vector3> triangles;
    for (int row = 0; row <= slices; row++) {
        for (int col = 0; col <= slices; col++) {
            float x = static_cast<float>(row) / static_cast<float>(slices) * W;
            float y = static_cast<float>(col) / static_cast<float>(slices) * H;

            points.emplace_back(x, y, 0);
        }
    }

    for (int row = 0; row < slices; row++) {
        for (int col = 0; col < slices; col++) {
            int bottomLeft = row * (slices + 1) + col;
            int bottomRight = row * (slices + 1) + col + 1;
            int topLeft = (row + 1) * (slices + 1) + col;
            int topRight = (row + 1) * (slices + 1) + col + 1;

            triangles.emplace_back(points[bottomLeft]);
            triangles.emplace_back(points[topLeft]);
            triangles.emplace_back(points[bottomRight]);

            triangles.emplace_back(points[bottomRight]);
            triangles.emplace_back(points[topRight]);
            triangles.emplace_back(points[topLeft]);
        }
    }

    return triangles;
}

std::vector<Vector3> makeSquare() {

    std::vector<Vector3> triangles;

    Vector3 bottomLeft = {200.0f, 400.f, 0};
    Vector3 bottomRight = {400.0f, 400.f, 0};
    Vector3 topLeft = {200.0f, 600.f, 0};
    Vector3 topRight = {400.0f, 600.f, 0};


    triangles.emplace_back(bottomLeft);
    triangles.emplace_back(bottomRight);

    triangles.emplace_back(bottomRight);
    triangles.emplace_back(topRight);

    triangles.emplace_back(topRight);
    triangles.emplace_back(topLeft);

    triangles.emplace_back(topLeft);
    triangles.emplace_back(bottomLeft);


    return triangles;
}