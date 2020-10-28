#ifndef __COMPONENT_TRANSFORMATION_H_
#define __COMPONENT_TRANSFORMATION_H_

#include "Component.h"
#include "MathGeoLib/MathGeoLib.h"

class C_Transform : public Component {
public:
	C_Transform(Component::Type type, GameObject* owner);
	~C_Transform();

public:

	Component::Type GetComponentType() override;
	float3 GetPosition();
	float3 GetScale();
	float3 GetEulerRotation();
	Quat GetQuaternionRotation();

public:
	float4x4 transform;
	float4x4 global_transform;
	float4x4 global_transformT;

	float3 position;
	float3 scale;
	float3 eulerRotation;
	Quat quaternionRotation;
	

};
#endif // !__COMPONENT_TRANSFORMATION_H_
