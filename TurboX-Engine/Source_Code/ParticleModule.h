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

	void Init(EmitterInstance* emitterInstance);
	virtual void Spawn(EmitterInstance* emitterInstance); //It creates a new particle or re-spawns an existing one through object polling
	virtual void Update(EmitterInstance* emitterInstance);
	virtual void Reset();
	virtual void CleanUp();
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
 
// ---------- CUSTOM PARTICLE ----------

class CustomParticle : public ParticleModule
{
public:
	CustomParticle(GameObject* owner);
	~CustomParticle();

	void CleanUp() override;

	Type GetType() { return Type::Custom; };
};

// ---------- SMOKE PARTICLE EMITTER ----------

class Smoke : public ParticleModule
{
public:
	Smoke(GameObject* owner);
	~Smoke();

	void CleanUp() override;

	Type GetType() { return Type::Smoke; };
};

// ---------- FIREWORK ----------

class Firework : public ParticleModule
{
public:
	Firework(GameObject* owner);
	~Firework();

	void Update(EmitterInstance* emitterInstance) override;
	void Spawn(EmitterInstance* emitterInstance) override;

	void CleanUp() override;

	Color GetRandomColor(range<Color> r);
	
	Type GetType() { return Type::Firework; };
public:
	GameObject* fireworkOwner;
private:
	float lifeTime;
	float currentTime;
	range <Color> rangeColor;
};

#endif // !__PARTICLE_MODULE_H__