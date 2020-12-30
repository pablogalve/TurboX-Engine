#include "Application.h"
#include "EmitterInstance.h"
#include "ParticleEmitter.h"
#include "ModuleSceneLoader.h"
#include "glew/glew.h"
#include "Color.h"
#include "Component_ParticleSystem.h"
#include "ModuleTimeManagement.h"

EmitterInstance::EmitterInstance()
{
    existing_particles = 0;
    particleReference = new Particle();
    particleReference->position = { 0,0,0 };
    particleReference->lifetime = 120;
    particleReference->worldRotation = { 0,0,0,1 };
    particleReference->color = Red;
    particleReference->velocity = 2.0f;
    particleReference->direction = { 0,1,0 };
}

void EmitterInstance::Init(ParticleEmitter* emitterReference)
{
    this->emitter = emitterReference;
    if (this->emitter != nullptr) {
        //particles_vector.resize(emitter->maxParticles);
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
    DrawParticles();
}

void EmitterInstance::DrawParticles()
{
    for (size_t i = 0; i < particles_vector.size(); i++)
    {
        particles_vector[i].position += particles_vector[i].velocity * particles_vector[i].direction * App->timeManagement->GetDeltaTime();

        glColor4f(0.2f, 0.2f, 1.0f, 1.0f);
        glPointSize(20);
        glBegin(GL_POINTS);
        glVertex3f(particles_vector[i].position.x, particles_vector[i].position.y, particles_vector[i].position.z);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glEnd();
    }
}

void EmitterInstance::CreateParticle()
{
    float3 direction = { 0,1,0 };

    Particle* newParticle = new Particle(particleReference);
    
    newParticle->position.x += owner->GetRandomFloat(owner->positionz);

    if (newParticle != nullptr) 
    { 
        particles_vector.push_back(newParticle);
        existing_particles++; 
    }
    else MY_LOG("Error creating particles in the Particle Emitter Instance. newParticle was nulltr.")
}

void EmitterInstance::SpawnParticle()
{
    int spawnAmount = 10;
    for (size_t i = 0; i < spawnAmount; i++)
    {
        //if (existing_particles < particles_vector.size()) {
        if (existing_particles < 10) {
            //Create new particles until the vector is full
            CreateParticle();
        }
        else {
            //TODO: Re-spawn inactive particles            
        }
    }
}