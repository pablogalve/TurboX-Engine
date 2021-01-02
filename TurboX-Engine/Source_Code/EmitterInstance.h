#ifndef __EMITTER_INSTANCE_H__
#define __EMITTER_INSTANCE_H__

#include "Globals.h"
#include <vector>
#include "Particle.h"

class C_ParticleSystem;
class ParticleEmitter;

class EmitterInstance
{
public:
	EmitterInstance();

	void Init(ParticleEmitter* emitterReference);
	void UpdateModules();
	void DrawParticles(); //TODO: DrawParticles()
	
	void SpawnParticle(); //It creates a new particle or re-spawns an existing one through object polling
	void DeActivateParticles(); 
	unsigned int GetFirstUnusedParticle();
	float3 SetRandomDirection();

	void UpdateParticleReference();
private:	
	void CreateParticle(); //Function to create new particles
public:
	std::vector<Particle> particles_vector;
	ParticleEmitter* emitter;
	C_ParticleSystem* owner;

	Particle* particleReference;

private:
	uint existing_particles;
	uint activeParticles;
	uint lastUsedParticle;
};
#endif // !__EMITTER_INSTANCE_H__