#include "Component_ParticleSystem.h"

C_ParticleSystem::C_ParticleSystem(Component::Type type, GameObject* owner) :Component(type, owner)
{
	resourceParticleSystem = nullptr;
	lifetime = 0;
}

C_ParticleSystem::~C_ParticleSystem()
{
}

Component::Type C_ParticleSystem::GetComponentType()
{
	return Component::Type::ParticleSystem;
}

void C_ParticleSystem::Update()
{
	for (size_t i = 0; i < emitters.size(); i++)
	{
		emitters[i].UpdateModules();
	}
}

void C_ParticleSystem::Reset()
{
}

void C_ParticleSystem::Save()
{
}

void C_ParticleSystem::Load()
{
}
