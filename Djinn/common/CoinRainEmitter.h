#ifndef VVR_OGL_LABORATORY_RAINEMITTER_H
#define VVR_OGL_LABORATORY_RAINEMITTER_H
#include "IntParticleEmitter.h"

class CoinRainEmitter : public IntParticleEmitter {
    public:
        CoinRainEmitter(Drawable* _model, int number);

        bool checkForCollision(particleAttributes& particle);

        int active_particles = 0; //number of particles that have been instantiated
        void createNewParticle(int index) override;
        void updateParticles(float time, float dt, glm::vec3 camera_pos = glm::vec3(0, 0, 0)) override;
};

#endif //VVR_OGL_LABORATORY_RAINEMITTER_H