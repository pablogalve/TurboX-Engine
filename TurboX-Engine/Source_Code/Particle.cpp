#include "Particle.h"

Particle::Particle()
{
}

Particle::Particle(Particle* particleReference)
{
	position = particleReference->position;
	worldRotation = particleReference->worldRotation;
	lifetime = particleReference->lifetime;
	velocity = particleReference->velocity;
	direction = particleReference->direction;
	active = true;
}

Particle::~Particle()
{
}

void Particle::Draw()
{
	
}