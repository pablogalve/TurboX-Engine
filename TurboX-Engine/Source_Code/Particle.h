#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "MathGeoLib/Math/float3.h"
#include "MathGeoLib/Math/float4.h"
#include "MathGeoLib/Math/Quat.h"

class Particle {
public:
	Particle();
	Particle(Particle* particleReference);
	~Particle();

public:
	float3 position;
	Quat worldRotation;
	float lifetime;
	float4 velocity;
};

#endif // !__PARTICLE_H__