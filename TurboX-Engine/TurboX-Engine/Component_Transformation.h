#ifndef __COMPONENT_TRANSFORMATION_H_
#define __COMPONENT_TRANSFORMATION_H_

#include "Component.h"
#include "MathGeoLib/MathGeoLib.h"

class C_Transform : public Component {
public:
	C_Transform(Component::Type type, GameObject* owner);
	~C_Transform();

public:

	float3 position;
	float3 scale;
	Quat rotation;

};
#endif // !__COMPONENT_TRANSFORMATION_H_
