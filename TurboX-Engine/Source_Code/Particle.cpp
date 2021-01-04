#include "Particle.h"

Particle::Particle()
{
}

Particle::Particle(Particle* particleReference)
{
	position = particleReference->position;
	lifetime = particleReference->lifetime;
	velocity = particleReference->velocity;
	direction = particleReference->direction;
	size = particleReference->size;
	dirVariation = particleReference->dirVariation;
	active = true;
	billboard = particleReference->billboard;
}

Particle::~Particle()
{
}

void Particle::Draw()
{
	
}