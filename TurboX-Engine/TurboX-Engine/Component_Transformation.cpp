#include "Component_Transformation.h"

C_Transform::C_Transform(Component::Type type, GameObject* owner):Component(type, owner)
{
	this->owner = owner;
	position = float3{ 0,0,0 };
	scale = float3{ 1,1,1 };
	rotationVec = float3{ 0,0,0 };
	localMatrix = float4x4::identity;
	globalMatrix = float4x4::identity;
	rotation = Quat{ 0.0f,0.0f,0.0f,1.0f };
}

C_Transform::~C_Transform()
{
}

Component::Type C_Transform::GetComponentType()
{
	return Component::Type::Transform;
}

float3 C_Transform::GetPosition()
{

	return position;
}

float3 C_Transform::GetScale()
{

	return scale;
}

void C_Transform::SetRotation(float3 rot)
{
	rotationVec = rot;
}

void C_Transform::SetQuaternionRotation(Quat quatRot)
{
	rotation = quatRot;
}

void C_Transform::SetPosition(float3 pos)
{
	position = pos;
}

void C_Transform::SetScale(float3 scl)
{
	scale = scl;
}

float3 C_Transform::GetEulerRotation()
{
	return rotationVec;
}

Quat C_Transform::GetQuaternionRotation()
{
	return rotation;
}

void C_Transform::RecalculateMatrix()
{
	localMatrix.Set(float4x4::FromTRS(position, rotation, scale));
}
