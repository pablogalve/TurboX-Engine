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
	void SetPosition(float3 pos);
	void SetScale(float3 scl);
	void SetRotation(float3 rot);
	void SetQuaternionRotation(Quat quadRot);
	Quat GetQuaternionRotation();
	void RecalculateMatrix();

	bool Save(Config* data) override;

public:
	float3 position = { 0.0f,0.0f,0.0f };
	float3 rotationVec = { 0.0f,0.0f,0.0f };
	float3 scale = { 1.0f,1.0f,1.0f };

	float4x4 localMatrix = float4x4::identity;
	float4x4 globalMatrix = float4x4::identity;

	Quat rotation = { 0.0f,0.0f,0.0f,1.0f };
	
	bool changed;

};
#endif // !__COMPONENT_TRANSFORMATION_H_
