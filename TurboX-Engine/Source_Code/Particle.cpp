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

void Particle::Draw()
{
	
}

void ParticleInfo::Set(float sSize, float eSize, float sSpin, float eSpin, float spd, uint life, float3 pos, float3 dir, float3 grav, Color sColor, Color eColor)
{
	startSize = sSize;
	endSize = eSize;

	startSpin = sSpin;
	endSpin = eSpin;

	speed = spd;
	lifetime = life;

	startPosition = pos;
	direction = dir;
	gravity = grav;

	startColor = sColor;
	endColor = eColor;
}
