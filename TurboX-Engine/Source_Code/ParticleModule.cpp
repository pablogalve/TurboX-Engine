#include "ParticleModule.h"
#include "ModuleTimeManagement.h"
#include "Libraries/MathGeoLib/MathGeoLib.h"

ParticleModule::ParticleModule()
{
}

void ParticleModule::Spawn(EmitterInstance* emitterInstance)
{

}

void ParticleModule::Update(EmitterInstance* emitterInstance)
{
	
}

void ParticleModule::Save()
{

}

void ParticleModule::Load()
{
}

Firework::Firework(GameObject* owner)
{
	fireworkOwner = owner;
	currentTime = 0.0f;
	lifeTime = 5.0f;
	fireworkReference.active = false;
	fireworkReference.billboard = nullptr;
	fireworkReference.color = Red;
	fireworkReference.direction = { 0,0,0 };
	fireworkReference.dirVariation = 360.0f;
	fireworkReference.distanceToCamera = NULL;
	fireworkReference.lifetime = 2.0;
	fireworkReference.position = fireworkOwner->transform->position;
	fireworkReference.size = 10.0f;
	fireworkReference.velocity = 0.5f;
}

Firework::~Firework()
{

}

void Firework::Update(EmitterInstance* emitterInstance)
{
	if (currentTime < lifeTime)
	{

		float3 lastPos = fireworkOwner->transform->position;

		fireworkOwner->transform->SetPosition({ lastPos.x, lastPos.y + 0.1f, lastPos.z });
		fireworkReference.position = fireworkOwner->transform->position;
		currentTime + App->timeManagement->GetDeltaTime();
	}
}