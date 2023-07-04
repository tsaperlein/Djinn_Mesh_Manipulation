#include "CoinRainEmitter.h"
#include <iostream>
#include <algorithm>

CoinRainEmitter::CoinRainEmitter(Drawable *_model, int number) : IntParticleEmitter(_model, number) {}

void CoinRainEmitter::updateParticles(float time, float dt, glm::vec3 camera_pos) {

    float height_threshold = -3.439f;

    //This is for the fountain to slowly increase the number of its particles to the max amount
    //instead of shooting all the particles at once
    if (active_particles < number_of_particles) {
        int batch = 50;
        int limit = std::min(number_of_particles - active_particles, batch) * dt * 0.8f;
        for (int i = 0; i < limit; i++) {
            createNewParticle(active_particles);
            active_particles++;
        }
    }
    else {
        active_particles = number_of_particles; //In case we resized our ermitter to a smaller particle number
    }

    for(int i = 0; i < active_particles; i++){
        particleAttributes & particle = p_attributes[i];

        if(particle.life == 0.0f || checkForCollision(particle)){
            createNewParticle(i);
        }

        particle.rot_angle += 90*dt; 

        particle.position = particle.position + particle.velocity*dt + particle.accel*(dt*dt)*0.5f;
        particle.velocity = particle.velocity + particle.accel*dt;

        auto bill_rot = calculateBillboardRotationMatrix(particle.position, camera_pos);
        particle.rot_axis = glm::vec3(bill_rot.x, bill_rot.y, bill_rot.z);
        particle.rot_angle = glm::degrees(bill_rot.w);
        particle.dist_from_camera = length(particle.position - camera_pos);

        particle.life = (height_threshold - particle.position.y) / (height_threshold - emitter_pos.y);
    }
}

bool CoinRainEmitter::checkForCollision(particleAttributes& particle)
{
    return particle.position.y < -3.438f;
}

void CoinRainEmitter::createNewParticle(int index)
{
    particleAttributes & particle = p_attributes[index];

    particle.position = emitter_pos + glm::vec3(3 - RAND*6, -1 * RAND, 3 - RAND*6) * 4.0f;
    particle.velocity = glm::vec3(0,-10.0f,0);

    particle.mass = RAND + 0.5f;
    particle.rot_axis = glm::normalize(glm::vec3(1 - 2*RAND, 1 - 2*RAND, 1 - 2*RAND));
    particle.accel = glm::vec3(0.0f, -9.8f, 0.0f); //gravity force
    particle.rot_angle = RAND*360;
    particle.life = 1.0f; //mark it alive
}
