#include "Component_ParticleSystem.h"

C_ParticleSystem::C_ParticleSystem(Component::Type type, GameObject* owner) :Component(type, owner)
{
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
