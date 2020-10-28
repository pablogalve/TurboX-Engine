#include "Component_Transformation.h"

C_Transform::C_Transform(Component::Type type, GameObject* owner):Component(type, owner)
{
	this->owner = owner;
	position = float3{ 0,0,0 };
	scale = float3{ 1,1,1 };
	eulerRotation = float3{ 0,0,0 };
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

float3 C_Transform::GetEulerRotation()
{

	return eulerRotation;
}

Quat C_Transform::GetQuaternionRotation()
{
	return quaternionRotation;
}
