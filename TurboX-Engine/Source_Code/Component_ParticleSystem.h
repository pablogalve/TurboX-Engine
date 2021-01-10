#ifndef __COMPONENT_PARTICLE_SYSTEM_H__
#define __COMPONENT_PARTICLE_SYSTEM_H__

#include "Component.h"
#include "Component_Material.h"
#include <vector>
#include <map>
#include "EmitterInstance.h"
#include "ResourceMesh.h"

class GameObject;

class C_ParticleSystem : public Component {
public:
	C_ParticleSystem(Component::Type type, GameObject* owner);
	~C_ParticleSystem();

	Component::Type GetComponentType() override;

	void Init();
	void Update() override;
	void Reset(); //TODO: Reset()

	void Save(); //TODO: Save()
	void Load(); //TODO: Update()

	float GetRandomFloat(range<float> number);
	uint GetRandomUint(range<uint> number);
	
	void AddMaterial(std::map<uint, Resource* > resources);
	void UpdateParticleGUI(Particle* newParticleReference);
public:
	std::vector<EmitterInstance> emitters;

public:
	Particle* particleReferenceGUI;
	int maxParticles;

	C_Material* particle_material;

	ResourceMesh* res_mesh;
};
#endif // !__COMPONENT_PARTICLE_SYSTEM_H__
