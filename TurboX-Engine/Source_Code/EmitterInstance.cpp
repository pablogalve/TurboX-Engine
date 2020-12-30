#include "EmitterInstance.h"
#include "ParticleEmitter.h"

EmitterInstance::EmitterInstance()
{
    existing_particles = 0;
    particleReference = new Particle();
    particleReference->position = { 0,0,0 };
    particleReference->lifetime = 120;
    particleReference->worldRotation = { 0,0,0,1 };
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

    SpawnParticle();
}

void EmitterInstance::DrawParticles()
{
}

void EmitterInstance::CreateParticle()
{
    float3 direction = { 0,1,0 };

    Particle* newParticle = new Particle(particleReference);

    if(newParticle != nullptr)existing_particles++;
    else MY_LOG("Error creating particles in the Particle Emitter Instance. newParticle was nulltr.")
}

void EmitterInstance::SpawnParticle()
{
    int spawnAmount = 10;
    for (size_t i = 0; i < spawnAmount; i++)
    {
        if (existing_particles < particles_vector.size()) {
            //Create new particles until the vector is full
            CreateParticle();
        }
        else {
            //TODO: Re-spawn inactive particles            
        }
    }
}