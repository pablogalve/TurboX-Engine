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
	color = particleReference->color;
	size = particleReference->size;
	dirVariation = particleReference->dirVariation;
	active = true;
	billboard = particleReference->billboard;
	distanceToCamera = 0.0f;
}

Particle::~Particle()
{
	billboard = nullptr;
}