#ifndef __EMITTER_INSTANCE_H__
#define __EMITTER_INSTANCE_H__

#include <vector>
#include "Particle.h"

class C_ParticleSystem;
class ParticleEmitter;

class EmitterInstance
{
public:
	EmitterInstance();

	void Init(); //TODO: Init()
	void UpdateModules(); //TODO: UpdateModules()
	void DrawParticles(); //TODO: DrawParticles()
public:
	std::vector<Particle> particle;
	ParticleEmitter* emitter;
	C_ParticleSystem* owner;
};

#endif // !__EMITTER_INSTANCE_H__