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
}

Particle::~Particle()
{
}
