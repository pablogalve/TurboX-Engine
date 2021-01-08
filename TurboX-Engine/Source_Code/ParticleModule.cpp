#include "ParticleModule.h"
#include "ModuleTimeManagement.h"
#include "Libraries/MathGeoLib/MathGeoLib.h"
#include "ModuleCamera3D.h"

ParticleModule::ParticleModule()
{
	existing_particles = 0;
	activeParticles = 0;
	lastUsedParticle = 0;
	particleReference = new Particle(); //TODO: Duplicate data. particleReference in EmitterInstance and C_ParticleSystem should only be initialized once
	particleReference->position = { 0,0,0 };
	particleReference->lifetime = 0;
	particleReference->billboard = nullptr;
}

void ParticleModule::Spawn(EmitterInstance* emitterInstance)
{
	if (existing_particles < emitterInstance->owner->maxParticles) {
		//Create new particles until the vector is full
		CreateParticle(emitterInstance);
	}
	else if (GetFirstUnusedParticle() != -1 && activeParticles < emitterInstance->owner->maxParticles)
	{
		uint index = GetFirstUnusedParticle();
		particles_vector[index].active = true; activeParticles++; //Reactivate particle        
		particleReference->position = emitterInstance->owner->owner->transform->position; //Get position from C_Transform

		//We update values from Particle Reference
		particles_vector[index].position = particleReference->position;
		particles_vector[index].lifetime = particleReference->lifetime;
		particles_vector[index].direction = particleReference->direction + SetRandomDirection();
		particles_vector[index].size = particleReference->size;
		particles_vector[index].velocity = particleReference->velocity;
		particles_vector[index].color = particleReference->color;
	}
}

void ParticleModule::Update(EmitterInstance* emitterInstance)
{
	
}

void ParticleModule::DrawParticles()
{
	for (size_t i = 0; i < particles_vector.size(); i++)
	{
		if (particles_vector[i].active)
		{
			//PARTICLES WITH MESH

			particles_vector[i].billboard->transform->position = particles_vector[i].position;
			particles_vector[i].billboard->transform->scale = float3(particles_vector[i].size);
			particles_vector[i].billboard->Draw(particles_vector[i].color);

			//PARTICLES WITH GL_POINTS
			/*particles_vector[i].position += particles_vector[i].velocity * particles_vector[i].direction * App->timeManagement->GetDeltaTime();
			particles_vector[i].lifetime -= App->timeManagement->GetDeltaTime();
			glColor4f(particles_vector[i].color.r, particles_vector[i].color.g, particles_vector[i].color.b, particles_vector[i].color.a);
			glPointSize(particles_vector[i].size);
			glBegin(GL_POINTS);
			glVertex3f(particles_vector[i].position.x, particles_vector[i].position.y, particles_vector[i].position.z);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glEnd();*/
		}
	}
}

void ParticleModule::DeActivateParticles()
{
	for (size_t i = 0; i < particles_vector.size(); i++)
	{
		if (particles_vector[i].lifetime <= 0)
		{
			if (particles_vector[i].active == true) {
				activeParticles--;
				particles_vector[i].active = false;
			}
		}
	}
}

void ParticleModule::Save()
{

}

void ParticleModule::Load()
{
}

float ParticleModule::CalculateParticleDistanceToCamera(Particle* p)
{
	return  sqrt(pow(App->camera->Position.x - p->position.x, 2) +
		pow(App->camera->Position.y - p->position.y, 2) +
		pow(App->camera->Position.z - p->position.z, 2) * 1.0);
}

unsigned int ParticleModule::GetFirstUnusedParticle()
{
	// first search from last used particle, this will usually return almost instantly
	for (unsigned int i = lastUsedParticle; i < particles_vector.size(); ++i) {
		if (particles_vector[i].lifetime <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// otherwise, do a linear search
	for (unsigned int i = 0; i < lastUsedParticle; ++i) {
		if (particles_vector[i].lifetime <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	return -1; //Return -1 if there are not unused particles
}

void ParticleModule::UpdateParticleReference(EmitterInstance* emitterInstance)
{
	particleReference->position = emitterInstance->owner->owner->transform->position;
	particleReference->lifetime = emitterInstance->owner->lifetime.min;
	particleReference->color = emitterInstance->owner->color.min;
	//particleReference->color = emitterInstance->owner->color.min; //TODO: Uncomment
	particleReference->direction = emitterInstance->owner->direction;
	particleReference->dirVariation = emitterInstance->owner->dirVariation;
	particleReference->size = emitterInstance->owner->size.min;
	particleReference->velocity = emitterInstance->owner->speed.min;
}

void ParticleModule::SortParticles(std::vector<Particle>& particles)
{
	std::sort(particles.begin(), particles.end(), ReOrderParticles());
}

void ParticleModule::CreateParticle(EmitterInstance* emitterInstance)
{
	Particle* newParticle = new Particle(particleReference);

	newParticle->billboard = (C_Billboard*)emitterInstance->owner->owner->CreateComponent(Component::Type::Billboard);

	if (newParticle != nullptr)
	{
		particles_vector.push_back(newParticle);
		existing_particles++;
		activeParticles++;
		//particles_vector[particles_vector.size()-1].color = owner->GetRandomColor(owner->color);
		particles_vector[particles_vector.size() - 1].direction = particleReference->direction + SetRandomDirection();
	}
	else MY_LOG("Error creating particles in the Particle Emitter Instance. newParticle was nulltr.")
}

float3 ParticleModule::SetRandomDirection()
{
	LCG lcg;
	float3 randomInSphere = float3::RandomSphere(lcg, { 0,0,0 }, 1);
	float3 variation = randomInSphere.Normalized();
	variation.x = variation.x * particleReference->dirVariation * DEGTORAD;
	variation.y = variation.y * particleReference->dirVariation * DEGTORAD;
	variation.z = variation.z * particleReference->dirVariation * DEGTORAD;

	float3 dir = particleReference->direction.Normalized() + variation;

	return dir.Normalized();
}

Firework::Firework(GameObject* owner)
{
	fireworkOwner = owner;
	currentTime = 0.0f;
	lifeTime = 5.0f;
	particleReference->active = false;
	particleReference->billboard = nullptr;
	particleReference->color = Red;
	particleReference->direction = { 0,0,0 };
	particleReference->dirVariation = 360.0f;
	particleReference->distanceToCamera = NULL;
	particleReference->lifetime = 2.0;
	particleReference->position = fireworkOwner->transform->position;
	particleReference->size = 10.0f;
	particleReference->velocity = 0.5f;
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
		particleReference->position = fireworkOwner->transform->position;
		currentTime += App->timeManagement->GetDeltaTime();
	}

	Spawn(emitterInstance);

	for (size_t i = 0; i < particles_vector.size(); i++)
	{
		if (particles_vector[i].active)
		{
			particles_vector[i].lifetime -= App->timeManagement->GetDeltaTime();
			particles_vector[i].position += particles_vector[i].velocity * particles_vector[i].direction * App->timeManagement->GetDeltaTime();
			particles_vector[i].distanceToCamera = CalculateParticleDistanceToCamera(&particles_vector[i]);
		}
	}

	SortParticles(particles_vector);

	DrawParticles();
	DeActivateParticles();
}

DefaultParticle::DefaultParticle(GameObject* owner)
{
}

DefaultParticle::~DefaultParticle()
{
}

void DefaultParticle::Update(EmitterInstance* emitterInstance)
{
	Spawn(emitterInstance);

	for (size_t i = 0; i < particles_vector.size(); i++)
	{
		if (particles_vector[i].active)
		{
			particles_vector[i].lifetime -= App->timeManagement->GetDeltaTime();
			particles_vector[i].position += particles_vector[i].velocity * particles_vector[i].direction * App->timeManagement->GetDeltaTime();
			particles_vector[i].distanceToCamera = CalculateParticleDistanceToCamera(&particles_vector[i]);
		}
	}

	SortParticles(particles_vector);

	DrawParticles();
	DeActivateParticles();
}