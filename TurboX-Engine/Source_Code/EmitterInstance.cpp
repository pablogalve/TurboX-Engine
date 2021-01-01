#include "Application.h"
#include "EmitterInstance.h"
#include "ParticleEmitter.h"
#include "ModuleSceneLoader.h"
#include "glew/glew.h"
#include "Color.h"
#include "Component_ParticleSystem.h"
#include "ModuleTimeManagement.h"
#include "GameObject.h"

EmitterInstance::EmitterInstance()
{
    existing_particles = 0;
    activeParticles = 0;
    particleReference = new Particle(); //TODO: Duplicate data. particleReference in EmitterInstance and C_ParticleSystem should only be initialized once
    particleReference->position = { 0,0,0 };
    particleReference->lifetime = 2;
    particleReference->worldRotation = { 0,0,0,1 };
    particleReference->color = Red;
    particleReference->velocity = 2.0f;
    particleReference->direction = { 0,1,0 };
    particleReference->size = 50;
    particleReference->dirVariation = 180;
    lastUsedParticle = 0;
}

void EmitterInstance::Init(ParticleEmitter* emitterReference)
{
    this->emitter = emitterReference;
    if (this->emitter != nullptr) {
        //TODO
        UpdateParticleReference();
    }
    else {
        MY_LOG("Error initializing the emitter instance in the Particle System.");
        particles_vector.resize(0);
    }
}

void EmitterInstance::UpdateModules()
{
    /*for (uint i = 0; i < emitter->modules.size() ; ++i)
    {
        //TODO: We are not using emitter->modules vector
        //emitter->modules[i]->Update(this);
    }*/

    SpawnParticle();
    DrawParticles();
    DeActivateParticles();       
}

void EmitterInstance::DrawParticles()
{
    for (size_t i = 0; i < particles_vector.size(); i++)
    {
        if(particles_vector[i].active)
        {
            //TODO: Move this code to its Update() functions instead of the Draw() function
            particles_vector[i].position += particles_vector[i].velocity * particles_vector[i].direction * App->timeManagement->GetDeltaTime();
            particles_vector[i].lifetime -= App->timeManagement->GetDeltaTime();
            glColor4f(particles_vector[i].color.r, particles_vector[i].color.g, particles_vector[i].color.b, particles_vector[i].color.a);
            glPointSize(particles_vector[i].size);
            glBegin(GL_POINTS);
            glVertex3f(particles_vector[i].position.x, particles_vector[i].position.y, particles_vector[i].position.z);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            glEnd();
        }
    }
}

void EmitterInstance::CreateParticle()
{    
    Particle* newParticle = new Particle(particleReference);  

    if (newParticle != nullptr) 
    { 
        particles_vector.push_back(newParticle);
        existing_particles++;
        activeParticles++;
        //particles_vector[particles_vector.size()-1].color = owner->GetRandomColor(owner->color);
        particles_vector[particles_vector.size()-1].direction = particleReference->direction + SetRandomDirection();
    }else MY_LOG("Error creating particles in the Particle Emitter Instance. newParticle was nulltr.")
}

void EmitterInstance::SpawnParticle()
{
    if (existing_particles < owner->maxParticles) {
        //Create new particles until the vector is full
        CreateParticle();
    }
    else if(GetFirstUnusedParticle() != -1 && activeParticles < owner->maxParticles)
    {
        uint index = GetFirstUnusedParticle();
        particles_vector[index].active = true; activeParticles++; //Reactivate particle        
        particleReference->position = owner->owner->transform->position; //Get position from C_Transform
        
        //We update values from Particle Reference
        particles_vector[index].position = particleReference->position;
        particles_vector[index].lifetime = particleReference->lifetime;
        particles_vector[index].direction = particleReference->direction + SetRandomDirection();
        particles_vector[index].size = particleReference->size;
        particles_vector[index].velocity = particleReference->velocity;
        particles_vector[index].color = particleReference->color;
    }
}

void EmitterInstance::DeActivateParticles()
{
    for (size_t i = 0; i < particles_vector.size(); i++)
    {
        if(particles_vector[i].lifetime <= 0)
        {
            if (particles_vector[i].active == true) {
                activeParticles--;
                particles_vector[i].active = false;
            }          
        }
    }
}

unsigned int EmitterInstance::GetFirstUnusedParticle()
{
    // first search from last used particle, this will usually return almost instantly
    for (unsigned int i = lastUsedParticle; i < particles_vector.size(); ++i) {
        if (particles_vector[i].lifetime <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    // otherwise, do a linear search
    for (unsigned int i = 0; i < lastUsedParticle; ++i) {
        if (particles_vector[i].lifetime <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    return -1; //Return -1 if there are not unused particles
}

float3 EmitterInstance::SetRandomDirection()
{
    LCG lcg;
    float3 randomInSphere = float3::RandomSphere(lcg, { 0,0,0 }, 1);
    float3 variation = randomInSphere.Normalized();
    variation.x = variation.x * particleReference->dirVariation * DEGTORAD;
    variation.y = variation.y * particleReference->dirVariation * DEGTORAD;
    variation.z = variation.z * particleReference->dirVariation * DEGTORAD;

    float3 dir = particleReference->direction.Normalized() + variation;

    return dir.Normalized();
}

void EmitterInstance::UpdateParticleReference()
{
    particleReference->lifetime = owner->lifetime.min;
    particleReference->color = Red;
    //particleReference->color = owner->color.min; //TODO: Uncomment
    particleReference->direction = owner->direction;
    particleReference->dirVariation = owner->dirVariation;
    particleReference->size = owner->size.min;
    particleReference->velocity = owner->speed.min;
}
