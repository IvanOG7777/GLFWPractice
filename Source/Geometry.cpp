//
// Created by elder on 6/27/2026.
//

#include "../Header/Geometry.h"

#include <iostream>

std::vector<glm::vec3> makeGrid(int slices) {
    std:: vector<glm::vec3> points;
    std:: vector<glm::vec3> triangles;
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

// creates a local space square.
std::vector<glm::vec3> makeSquare() {

    std::vector<glm::vec3> triangles;

    glm::vec3 bottomLeft = {-1.0f, -1.0f, 0};
    glm::vec3 bottomRight = {1.0f, -1.0f, 0};
    glm::vec3 topLeft = {-1.0f, 1.0f, 0};
    glm::vec3 topRight = {1.0f, 1.0f, 0};


    // for GL_LINES, connects points
    // triangles.emplace_back(bottomLeft);
    // triangles.emplace_back(bottomRight);
    //
    // triangles.emplace_back(bottomRight);
    // triangles.emplace_back(topRight);
    //
    // triangles.emplace_back(topRight);
    // triangles.emplace_back(topLeft);
    //
    // triangles.emplace_back(topLeft);
    // triangles.emplace_back(bottomLeft);

    // for GL_TRIANGLES, connects 3 points to make a triangle
    triangles.emplace_back(bottomLeft);
    triangles.emplace_back(bottomRight);
    triangles.emplace_back(topLeft);

    triangles.emplace_back(bottomRight);
    triangles.emplace_back(topRight);
    triangles.emplace_back(topLeft);

    return triangles;
}

std:: vector<glm::vec3> makeCube() {
    std::vector<glm::vec3> triangles;

    glm::vec3 bottomLeft = {-1.0f, -1.0f, 0};
    glm::vec3 bottomRight = {1.0f, -1.0f, 0};
    glm::vec3 topLeft = {-1.0f, 1.0f, 0};
    glm::vec3 topRight = {1.0f, 1.0f, 0};

    glm::vec3 bottomLeftZ = {-1.0f, -1.0f, -1};
    glm::vec3 bottomRightZ = {1.0f, -1.0f, -1};
    glm::vec3 topLeftZ = {-1.0f, 1.0f, -1};
    glm::vec3 topRightZ = {1.0f, 1.0f, -1};

    //Faces of the cube;

    // Front face
    triangles.emplace_back(bottomLeft);
    triangles.emplace_back(bottomRight);
    triangles.emplace_back(topLeft);

    triangles.emplace_back(bottomRight);
    triangles.emplace_back(topRight);
    triangles.emplace_back(topLeft);
    //

    //Back face
    triangles.emplace_back(bottomLeftZ);
    triangles.emplace_back(bottomRightZ);
    triangles.emplace_back(topLeftZ);

    triangles.emplace_back(bottomRightZ);
    triangles.emplace_back(topRightZ);
    triangles.emplace_back(topLeftZ);
    //

    //Top face
    triangles.emplace_back(topLeft);
    triangles.emplace_back(topRight);
    triangles.emplace_back(topLeftZ);

    triangles.emplace_back(topRight);
    triangles.emplace_back(topRightZ);
    triangles.emplace_back(topLeftZ);
    //

    // Bottom face
    triangles.emplace_back(bottomLeft);
    triangles.emplace_back(bottomRight);
    triangles.emplace_back(bottomLeftZ);

    triangles.emplace_back(bottomRight);
    triangles.emplace_back(bottomRightZ);
    triangles.emplace_back(bottomLeftZ);
    //

    // Left face
    triangles.emplace_back(bottomLeft);
    triangles.emplace_back(bottomLeftZ);
    triangles.emplace_back(topLeft);

    triangles.emplace_back(bottomLeftZ);
    triangles.emplace_back(topLeftZ);
    triangles.emplace_back(topLeft);
    //

    // Right face
    triangles.emplace_back(bottomRight);
    triangles.emplace_back(bottomRightZ);
    triangles.emplace_back(topRight);

    triangles.emplace_back(bottomRightZ);
    triangles.emplace_back(topRightZ);
    triangles.emplace_back(topRight);
    //

    return triangles;
}

std::vector<glm::vec3> makeSphere(float radius) {
    std:: vector <glm::vec3> points;
    std:: vector <glm::vec3> triangles;

    int stacks = 32; // rows
    int sectors = 64; // columns

    for (int row = 0; row <= stacks; row++) {
        for (int col = 0; col <= sectors; col++) {
            float phi = glm::pi<float>() * static_cast<float>(row) / static_cast<float>(stacks);
            float theta = (2 * glm::pi<float>()) * static_cast<float>(col) / static_cast<float>(sectors);

            float x = std:: cosf(theta) * std:: sinf(phi);
            float y = std:: cosf(phi);
            float z = std:: sinf(theta) * std:: sinf(phi);

            points.emplace_back(x * radius, y * radius, z * radius);
        }
    }

    for (int row = 0; row < stacks; row++) {
        for (int col = 0; col < sectors; col++) {
            int bottomLeft = row * (sectors + 1) + col;
            int bottomRight = row * (sectors + 1) + (col + 1);
            int topLeft = (row + 1) * (sectors + 1) + col;
            int topRight = (row + 1) * (sectors + 1) + (col + 1);

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

int index (int x, int y, int z, int squaresInY, int squaresInZ) {
    return (x * (squaresInY + 1) * (squaresInZ + 1)) + (y * (squaresInZ + 1)) + z;
}

std::vector<glm::vec3> makeGrid3D() {
    std:: vector<glm::vec3> points;
    std:: vector<glm::vec3> lines;

    int xWidth = 4;
    int yWidth = 4;
    int zWidth = 4;
    int squaresInX = 4;
    int squaresInY = 4;
    int squaresInZ = 4;

    int deltaX = xWidth / squaresInX;
    int deltaY = yWidth / squaresInY;
    int deltaZ = zWidth / squaresInZ;

    for (int x = 0; x <= squaresInX; x++) {
        for (int y = 0; y <= squaresInY; y++) {
            for (int z = 0; z <= squaresInZ; z++) {
                int xVal = -(xWidth/2) + x*deltaX;
                int yVal = -(yWidth/2) + y*deltaY;
                int zVal = -(zWidth/2) + z*deltaZ;
                points.emplace_back(xVal, yVal, zVal);
            }
        }
    }

    for (auto &point : points) {
        std:: cout << "(" << point.x << ", " << point.y << ", " << point.z << ")" << std:: endl;
    }

    for (int x = 0; x < squaresInX; x++) {
        for (int y = 0; y < squaresInY; y++) {
            for (int z = 0; z < squaresInZ; z++) {

                int frontBottomLeft = index(x, y, z, squaresInY, squaresInZ);
                int frontBottomRight = index(x + 1, y, z, squaresInY, squaresInZ);
                int frontTopLeft = index(x, y + 1, z, squaresInY, squaresInZ);
                int frontTopRight = index(x + 1, y + 1, z, squaresInY, squaresInZ);

                int backBottomLeft = index(x, y , z + 1, squaresInY, squaresInZ);
                int backBottomRight = index(x + 1, y, z + 1, squaresInY, squaresInZ);
                int backTopLeft = index(x, y + 1, z + 1, squaresInY, squaresInZ);
                int backTopRight = index(x + 1, y + 1, z + 1, squaresInY, squaresInZ);

                lines.emplace_back(points[frontBottomLeft]);
                lines.emplace_back(points[frontBottomRight]);

                lines.emplace_back(points[frontBottomRight]);
                lines.emplace_back(points[frontTopRight]);

                lines.emplace_back(points[frontTopRight]);
                lines.emplace_back(points[frontTopLeft]);

                lines.emplace_back(points[frontTopLeft]);
                lines.emplace_back(points[frontBottomLeft]);


                lines.emplace_back(points[backBottomLeft]);
                lines.emplace_back(points[backBottomRight]);

                lines.emplace_back(points[backBottomRight]);
                lines.emplace_back(points[backTopRight]);

                lines.emplace_back(points[backTopRight]);
                lines.emplace_back(points[backTopLeft]);

                lines.emplace_back(points[backTopLeft]);
                lines.emplace_back(points[backBottomLeft]);


                lines.emplace_back(points[frontBottomLeft]);
                lines.emplace_back(points[backBottomLeft]);

                lines.emplace_back(points[frontBottomRight]);
                lines.emplace_back(points[backBottomRight]);

                lines.emplace_back(points[frontTopLeft]);
                lines.emplace_back(points[backTopLeft]);

                lines.emplace_back(points[frontTopRight]);
                lines.emplace_back(points[backTopRight]);

            }
        }
    }


    return lines;
}
