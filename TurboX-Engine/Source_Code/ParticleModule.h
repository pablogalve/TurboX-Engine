#ifndef __PARTICLE_MODULE_H__
#define __PARTICLE_MODULE_H__
#include "GameObject.h"
#include "Particle.h"
#include <string>
#include "Globals.h"
#include "Libraries/pcg-c-basic-0.9/pcg_basic.h"

struct ReOrderParticles
{
	inline bool operator() (const Particle& particle1, const Particle& particle2)
	{
		return (particle1.distanceToCamera > particle2.distanceToCamera);
	}
};

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

	virtual void Spawn(EmitterInstance* emitterInstance); //It creates a new particle or re-spawns an existing one through object polling
	virtual void Update(EmitterInstance* emitterInstance); //TODO: Update()
	void DrawParticles();
	void DeActivateParticles();
	void Save(); //TODO: Save()
	void Load(); //TODO: Load()

	float CalculateParticleDistanceToCamera(Particle* p);	
	void UpdateParticleReference(EmitterInstance* emitterInstance);
protected:
	void SortParticles(std::vector<Particle>& particles);
	void CreateParticle(EmitterInstance* emitterInstance); //Function to create new particles
	float3 SetRandomDirection();
	unsigned int GetFirstUnusedParticle();
public:
	Particle* particleReference;
	std::string name;
protected:
	std::vector<Particle> particles_vector;
	uint existing_particles;
	uint activeParticles;
	uint lastUsedParticle;
};

class DefaultParticle : public ParticleModule
{
public:
	DefaultParticle(GameObject* owner);
	~DefaultParticle();

	void Update(EmitterInstance* emitterInstance) override;

public:
	GameObject* fireworkOwner;	
private:
	Particle fireworkReference;
	float lifeTime;
	float currentTime;	
};

class Firework : public ParticleModule
{
public:
	Firework(GameObject* owner);
	~Firework();

	void Update(EmitterInstance* emitterInstance) override;
	void Spawn(EmitterInstance* emitterInstance) override;

	void CleanUp();

	Color GetRandomColor(range<Color> r);
	
public:
	GameObject* fireworkOwner;
private:
	float lifeTime;
	float currentTime;
	range <Color> rangeColor;
};

#endif // !__PARTICLE_MODULE_H__