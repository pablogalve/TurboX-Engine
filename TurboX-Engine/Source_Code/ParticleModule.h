#ifndef __PARTICLE_MODULE_H__
#define __PARTICLE_MODULE_H__
#include "GameObject.h"
#include "Particle.h"

class EmitterInstance;

class ParticleModule {
public:
	enum Type {
		None,
		Custom,
		Smoke, 
		Firework
	};

	ParticleModule();

	void Spawn(EmitterInstance* emitterInstance); //TODO: Spawn()
	virtual void Update(EmitterInstance* emitterInstance); //TODO: Update()
	void Save(); //TODO: Save()
	void Load(); //TODO: Load()
};

class Firework : public ParticleModule
{
public:
	Firework(GameObject* owner);
	~Firework();

	void Update(EmitterInstance* emitterInstance) override;

public:
	GameObject* fireworkOwner;

private:
	Particle fireworkReference;
	float lifeTime;
	float currentTime;
};

#endif // !__PARTICLE_MODULE_H__