//
// Created by elder on 6/27/2026.
//

#ifndef GLFWPRACTICE_GEOMETRY_H
#define GLFWPRACTICE_GEOMETRY_H

#include <vector>
#include <glm/glm/glm.hpp>
#include "Constants.h"
#include "Camera.h"

std:: vector<glm::vec3> makeGrid(int slices);

std::vector<glm::vec3> makeSquare();

std:: vector<glm::vec3> makeCube();

std:: vector<glm::vec3> makeSphere();

#endif //GLFWPRACTICE_GEOMETRY_H