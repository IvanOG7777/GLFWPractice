//
// Created by elder on 6/27/2026.
//

#ifndef GLFWPRACTICE_GEOMETRY_H
#define GLFWPRACTICE_GEOMETRY_H

#include <vector>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "Constants.h"
#include "Camera.h"

std:: vector<glm::vec3> makeGrid(int slices);

std::vector<glm::vec3> makeSquare();

std:: vector<glm::vec3> makeCube();

std:: vector<glm::vec3> makeSphere(float radius);

std:: vector<glm::vec3> makeGrid3D();

#endif //GLFWPRACTICE_GEOMETRY_H