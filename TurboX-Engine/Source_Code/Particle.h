#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "MathGeoLib/Math/float3.h"
#include "MathGeoLib/Math/float4.h"
#include "MathGeoLib/Math/Quat.h"
#include "Color.h"
#include "Component_Transformation.h"
#include "Component_Billboard.h"

class ParticleInfo
{
public:

	float speed;

	uint lifetime;

	float startSize;
	float endSize;

	float startSpin;
	float endSpin;

	float3 direction;
	float3 startPosition;
	float3 gravity;

	Color startColor;
	Color endColor;


	C_Billboard* billboard = nullptr;

	void Set(float sSize = 0, float eSize = 0, float sSpin = 0, float eSpin = 0, float spd = 0, uint life = 0, float3 pos = float3::zero, float3 dir = float3::zero, float3 gravity = float3::zero, Color sColor = White, Color eColor = White);
};

class Particle {
public:
	Particle();
	Particle(Particle* particleReference);
	~Particle();

	void Draw();

public:
	float3 position;
	Quat worldRotation;
	float lifetime;
	float4 velocity;

private:
	ParticleInfo info;
};

#endif // !__PARTICLE_H__