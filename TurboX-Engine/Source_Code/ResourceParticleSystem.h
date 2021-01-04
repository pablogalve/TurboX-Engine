#ifndef __RESOURCE_PARTICLE_SYSTEM_H__
#define __RESOURCE_PARTICLE_SYSTEM_H__

#include "ParticleEmitter.h"

class ResourceParticleSystem : public Resource
{
public:
	ResourceParticleSystem(uint UUID);
	virtual ~ResourceParticleSystem();

public:
	std::vector<ParticleEmitter> emitters;
};
#endif// !__RESOURCE_PARTICLE_SYSTEM_H__