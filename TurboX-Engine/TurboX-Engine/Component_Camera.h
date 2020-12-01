#pragma once
#include "Component.h"

class C_Camera : public Component
{
public:

	C_Camera(Component::Type type, GameObject* owner);
	~C_Camera();

	void setAspectRatio(float aspectRatio);
	
	void DrawFrustum();

	bool ContainsAABB(const AABB& boundingBox);

	void RecalculateBB();

	void CameraBB();

public:

	Frustum frustum;
	AABB cameraBB;
};