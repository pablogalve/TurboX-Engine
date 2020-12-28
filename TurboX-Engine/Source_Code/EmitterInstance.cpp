#include "EmitterInstance.h"
#include "ParticleEmitter.h"

EmitterInstance::EmitterInstance()
{
}

void EmitterInstance::Init(ParticleEmitter* emitterReference)
{
    this->emitter = emitterReference;
    if (this->emitter != nullptr) {
        particles_vector.resize(emitter->maxParticles);
    }
    else {
        MY_LOG("Error initializing the emitter instance in the Particle System.");
        particles_vector.resize(0);
    }
}

void EmitterInstance::UpdateModules()
{
    for (uint i = 0; i < emitter->modules.size() ; ++i)
    {
        emitter->modules[i]->Update(this);
    }
}

void EmitterInstance::DrawParticles()
{
}
