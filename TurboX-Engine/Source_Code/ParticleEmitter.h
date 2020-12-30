#ifndef __PARTICLE_EMITTER_H__
#define __PARTICLE_EMITTER_H__

#include <vector>
#include "ResourceTexture.h"
#include "ParticleModule.h"

class ParticleEmitter{
public:
	ParticleEmitter();

	void Save();
	void Load();
public:
	ResourceTexture* particleTexture;
	std::vector<ParticleModule*> modules;

	uint maxParticles;
};

#endif // !__PARTICLE_EMITTER_H__
