#ifndef __EMITTER_INSTANCE_H__
#define __EMITTER_INSTANCE_H__

#include "Globals.h"
#include <vector>
#include "Particle.h"
#include <map>
#include <algorithm>

class C_ParticleSystem;
class ParticleEmitter;

class EmitterInstance
{
public:
	EmitterInstance();

	void Init(ParticleEmitter* emitterReference);
	void UpdateModules();
	void Draw();
	void UpdateParticleReference();
	void Reset();
public:	
	ParticleEmitter* emitter;
	C_ParticleSystem* owner;
};
#endif // !__EMITTER_INSTANCE_H__