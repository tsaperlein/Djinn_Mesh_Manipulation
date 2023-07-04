#include "SmokeEmitter.h"
#include <iostream>
#include <algorithm>

SmokeEmitter::SmokeEmitter(Drawable *_model, int number) : IntParticleEmitter(_model, number) {}

// Function to generate a Bézier curve
std::vector<glm::vec3> generateCurve(int numVertices, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
    std::vector<glm::vec3> vertices;
    vertices.reserve(numVertices);

    for (int i = 0; i < numVertices; i++) {
        // Interpolate between the control points using the Bézier curve formula
        float t = (float)i / (numVertices-1);
        float u = 1.0 - t;
        float tt = t*t;
        float uu = u*u;
        float uuu = uu * u;
        float ttt = tt * t;

        glm::vec3 p = uuu * p0;
        p += 3.0f * uu * t * p1;
        p += 3.0f * u * tt * p2;
        p += ttt * p3;

        vertices.push_back(p);
    }
    return vertices;
}

// Function to get the position of the particle in order to form the bezier curve
glm::vec3 bezier_position(float t, std::vector<glm::vec3> control_points) {
    // Interpolate between the control points using the Bézier curve formula
    int numVertices = control_points.size();
    int i0 = (int)(t * numVertices);
    i0 = glm::clamp(i0, 0, numVertices - 1);
    int i1 = i0 + 1;
    i1 = glm::clamp(i1, 0, numVertices - 1);
    float u = t * numVertices - i0;
    return (1 - u) * control_points[i0] + u * control_points[i1];
}

void SmokeEmitter::updateParticles(float time, float dt, glm::vec3 camera_pos) {

    float counter;

    // This is for the smoke to slowly increase the number of its particles to the max amount
    // instead of shooting all the particles at once
    if (active_particles < number_of_particles) {
        int batch = 50;
        int limit = std::min(number_of_particles - active_particles, batch);
        for (int i = 0; i < limit; i++) {
            createNewParticle(active_particles);
            active_particles++;
        }
    }
    else {
        // In case we resized our ermitter to a smaller particle number
        active_particles = number_of_particles;
    }

    for(int i = 0; i < active_particles; i++){
        particleAttributes & particle = p_attributes[i];

        if(particle.position.y > height_threshold || particle.life == 0.0f){
            createNewParticle(i);
        }

        // I want the particles to always go faster
        counter += 0.01f;
        particle.t += dt * counter;

        // Stop the counter to some point
        if (counter > 4.8f) {
            counter = 4.8f;
        }

        // particle.position = particle.position + particle.velocity*dt + particle.accel*(dt*dt)*0.5f;
        particle.position = bezier_position(particle.t, particle.control_points) + particle.velocity * dt + particle.accel * (dt * dt);

        particle.velocity = particle.velocity + particle.accel*dt;

        // Make the particles always look at the camera
        auto bill_rot = calculateBillboardRotationMatrix(particle.position, camera_pos);
        particle.rot_axis = glm::vec3(bill_rot.x, bill_rot.y, bill_rot.z);
        particle.rot_angle = glm::degrees(bill_rot.w);
        particle.dist_from_camera = length(particle.position - camera_pos);
        
        particle.life = (height_threshold - particle.position.y) / (height_threshold - emitter_pos.y);

        // Increase the mass of the particles accodring to their life
        if (particle.life > 0.7f && particle.life <= 1.0f) {
            particle.mass += 0.015f;
        }
        if (particle.life < 0.7f && particle.life > 0.3f) {
            particle.mass += 0.05f;
        }
        if (particle.life < 0.3f && particle.mass < 0.7f) {
            particle.mass += 0.1f;
        }
        if (particle.mass >= 0.7f) {
            particle.mass = 0.7f;
        }
    }
}

void SmokeEmitter::createNewParticle(int index){
    particleAttributes & particle = p_attributes[index];

    particle.velocity = glm::vec3(1,1,1);

    // Start the mass of the particles at a small size
    particle.mass = 0.02f;
    particle.rot_axis = glm::normalize(glm::vec3(1 - 2*RAND, 1 - 2*RAND, 1 - 2*RAND));
    particle.accel = glm::vec3(1,1,1);
    particle.rot_angle = RAND*360;
    particle.life = 1.0f; //mark it alive
    particle.t = 0;

    // Initialize the control points of the bezier curve, for every particle
    particle.p0 = glm::vec3(emitter_pos.x, emitter_pos.y, emitter_pos.z);
    particle.p1 = glm::vec3(0.5f * (RAND - RAND), 2.0f + 0.7f * (RAND - RAND), 0.5f * (RAND - RAND));
    particle.p2 = glm::vec3(5.0f + 2.5 * (RAND - RAND), 2.0f + 0.5f * (RAND - RAND), 2.5 * (RAND - RAND));
    particle.p3 = glm::vec3(5.0f + 2.0 * (RAND - RAND), 5.0f, 2.0 * (RAND - RAND));

    // Generate the curve
    particle.control_points = generateCurve(10, particle.p0, particle.p1, particle.p2, particle.p3);
    // Get the bezier position of the particle
    particle.position = emitter_pos + bezier_position(particle.t, particle.control_points);
}