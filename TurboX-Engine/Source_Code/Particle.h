#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "MathGeoLib/Math/float3.h"
#include "MathGeoLib/Math/float4.h"
#include "MathGeoLib/Math/Quat.h"
#include "Component_Billboard.h"
#include "Color.h"

class Particle {
public:
	Particle();
	Particle(Particle* particleReference);
	~Particle();

	void Draw();

public:
	float3 position;
	float lifetime;
	float velocity;
	float size;
	float dirVariation;
	Color color;
	float3 direction;
	bool active;

	C_Billboard* billboard;

};

#endif // !__PARTICLE_H__