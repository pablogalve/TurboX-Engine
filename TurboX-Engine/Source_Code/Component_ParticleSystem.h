#ifndef __COMPONENT_PARTICLE_SYSTEM_H__
#define __COMPONENT_PARTICLE_SYSTEM_H__

#include "Component.h"
#include <vector>
#include "EmitterInstance.h"
#include "ResourceParticleSystem.h"
class GameObject;

class C_ParticleSystem : public Component {
public:
	C_ParticleSystem(Component::Type type, GameObject* owner);
	~C_ParticleSystem();

	Component::Type GetComponentType() override;

	void Update(); //TODO: Update()
	void Reset(); //TODO: Reset()

	void Save(); //TODO: Save()
	void Load(); //TODO: Update()
public:
	std::vector<EmitterInstance> emitters;
	ResourceParticleSystem* resourceParticleSystem;

public:
	float lifetime;
};
#endif // !__COMPONENT_PARTICLE_SYSTEM_H__
