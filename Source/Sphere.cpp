//
// Created by elder on 7/6/2026.
//

#include "../Header/Sphere.h"

SphereParticle::SphereParticle() {
    mesh = {};
    position = {0, 0, 0};
    trailPositions.reserve(1000);
}

void SphereParticle::setPosition(float &passedX, float &passedY, float &passedZ) {
    position.x = passedX;
    position.y = passedY;
    position.z = passedZ;
}

void SphereParticle::setPosition(glm::vec3 &passedPosition) {
    position = passedPosition;
}

glm::vec3 SphereParticle::getPosition() {
    return position;
}

void SphereParticle::setMesh(std::vector<glm::vec3> &passedMesh) {
    mesh = passedMesh;
}

void SphereParticle::setTrailPosition(ParticleTrail &trail) {
    if (trailPositions.size() >= 1000) {
        trailPositions.erase(trailPositions.begin());
        trailPositions.emplace_back(trail);
    }

    trailPositions.emplace_back(trail);
}

std::vector<ParticleTrail> SphereParticle::getTrailPosition() {
    return trailPositions;
}
