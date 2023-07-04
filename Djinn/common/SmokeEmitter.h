#ifndef VVR_OGL_LABORATORY_SMOKEEMITTER_H
#define VVR_OGL_LABORATORY_SMOKEEMITTER_H
#include "IntParticleEmitter.h"

class SmokeEmitter : public IntParticleEmitter {
    public:
        SmokeEmitter(Drawable* _model, int number);

        // Stop rendering the particles after position.y > 5.0f
        float height_threshold = 5.0f;

        int active_particles = 0; //number of particles that have been instantiated
        void createNewParticle(int index) override;
        void updateParticles(float time, float dt, glm::vec3 camera_pos = glm::vec3(0, 0, 0)) override;
};

#endif //VVR_OGL_LABORATORY_SMOKEEMITTER_H