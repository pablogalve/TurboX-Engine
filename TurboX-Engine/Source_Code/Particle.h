#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Libraries/MathGeoLib/Math/float3.h"
#include "Libraries/MathGeoLib/Math/float4.h"
#include "Libraries/MathGeoLib/Math/Quat.h"
#include "Component_Billboard.h"
#include "Color.h"

class Particle {
public:
	Particle();
	Particle(Particle* particleReference);
	~Particle();
public:
	float3 position;
	float lifetime;
	float velocity;
	float size;
	float dirVariation;
	Color color;
	float3 direction;
	bool active;
	float distanceToCamera;

	C_Billboard* billboard;
};

#endif // !__PARTICLE_H__