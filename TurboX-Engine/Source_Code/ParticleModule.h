#ifndef __PARTICLE_MODULE_H__
#define __PARTICLE_MODULE_H__

class EmitterInstance;

class ParticleModule {
public:
	enum Type {
		None,
		Emitter
	};

	ParticleModule();

	void Spawn(EmitterInstance* emitterInstance); //TODO: Spawn()
	void Update(EmitterInstance* emitterInstance); //TODO: Update()
	void Save(); //TODO: Save()
	void Load(); //TODO: Load()
};
#endif // !__PARTICLE_MODULE_H__