#ifndef __RESOURCE_PARTICLE_SYSTEM_H__
#define __RESOURCE_PARTICLE_SYSTEM_H__

#include "Resource.h"
#include "Globals.h"

class Resource;

class ResourceParticleSystem : public Resource
{
public:
	ResourceParticleSystem(uint UUID);
	virtual ~ResourceParticleSystem();

	void CleanUp() override;
};
#endif// !__RESOURCE_PARTICLE_SYSTEM_H__