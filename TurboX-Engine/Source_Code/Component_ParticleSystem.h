#ifndef __COMPONENT_PARTICLE_SYSTEM_H__
#define __COMPONENT_PARTICLE_SYSTEM_H__

#include "Component.h"
#include <vector>
#include "EmitterInstance.h"
class GameObject;

class C_ParticleSystem : public Component {
public:
	C_ParticleSystem(Component::Type type, GameObject* owner);
	~C_ParticleSystem();

	void Update(); //TODO: Update()
	void Reset(); //TODO: Reset()

	void Save(); //TODO: Save()
	void Load(); //TODO: Update()
public:
	std::vector<EmitterInstance> emitters;
};
#endif // !__COMPONENT_PARTICLE_SYSTEM_H__
