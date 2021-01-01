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
	float lifetime;
	range <float> speed;
	//range <uint> lifetime;
	range <float> startSize;
	range <float> endSize;
	range <float> startSpin;
	range <float> endSpin;
	range <float3> direction;
	range <Color> startColor;
	range <Color> endColor;
	range <float> positionz;
};
#endif // !__COMPONENT_PARTICLE_SYSTEM_H__
