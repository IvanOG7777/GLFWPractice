//
// Created by elder on 6/27/2026.
//

#include "../Header/Geometry.h"

std::vector<Vector3> makeGrid(int slices) {
    std:: vector<Vector3> vertices;
    std:: vector<Vector3> triangles;
    for (int row = 0; row <= slices; row++) {
        for (int col = 0; col <= slices; col++) {
            float x = static_cast<float>(row) / static_cast<float>(slices) * W;
            float y = static_cast<float>(col) / static_cast<float>(slices) * H;

            vertices.emplace_back(x, y, 0);
        }
    }

    for (auto &verts: vertices) {
        std:: cout << verts << std:: endl;
    }

    return vertices;
}