#ifndef __COMPONENT_PARTICLE_SYSTEM_H__
#define __COMPONENT_PARTICLE_SYSTEM_H__

#include "Component.h"
#include <vector>
#include "EmitterInstance.h"
#include "ResourceParticleSystem.h"
class GameObject;

template <class T>
struct range
{
	T min; //Start
	T max; //Final
};

class C_ParticleSystem : public Component {
public:
	C_ParticleSystem(Component::Type type, GameObject* owner);
	~C_ParticleSystem();

	Component::Type GetComponentType() override;

	void Update() override;
	void Reset(); //TODO: Reset()

	void Save(); //TODO: Save()
	void Load(); //TODO: Update()

	float GetRandomFloat(range<float> number);
	uint GetRandomUint(range<uint> number);
	Color GetRandomColor(range<Color> r);

public:
	std::vector<EmitterInstance> emitters;
	ResourceParticleSystem* resourceParticleSystem;

public:
	int maxParticles;
	range <float> speed;
	range <float> lifetime;
	range <float> size;
	float3 direction;
	float dirVariation; //TODO: Randomize direction
	range <Color> color;
};
#endif // !__COMPONENT_PARTICLE_SYSTEM_H__
