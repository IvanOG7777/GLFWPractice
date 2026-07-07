//
// Created by elder on 7/6/2026.
//

#ifndef GLFWPRACTICE_SPHERE_H
#define GLFWPRACTICE_SPHERE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "Geometry.h"


struct ParticleTrail {
    glm::vec3 positon;
    glm::vec3 color = {1.0f, 1.0f, 1.0f};
};

class SphereParticle {
private:
    std::vector<glm::vec3> mesh;
    glm::vec3 position;
    std::vector<ParticleTrail> trailPositions;

public:

    SphereParticle();

    void setPosition(float passedX, float passedY, float passedZ);
    void setPosition(glm::vec3 &passedPosition);

    glm::vec3 getPosition();

    void setMesh(std::vector<glm::vec3> &passedMesh);

    void setTrailPosition(ParticleTrail &trail);
    void setTrailPosition(glm::vec3 position);
    std:: vector<ParticleTrail> getTrailPosition();

    size_t getTrailSize();

    ParticleTrail *getTrailData();

    size_t getMeshSize();

    glm::vec3 *getMeshData();
};




#endif //GLFWPRACTICE_SPHERE_H