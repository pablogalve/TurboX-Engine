#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Libraries/MathGeoLib/MathGeoLib.h"
#include <queue>
#include "Config_JSON.h"

class C_Camera;
class GameObject;

struct HitGameObject
{
	HitGameObject(GameObject* GO, float distance) : GO(GO), distance(distance)
	{}

	GameObject* GO = nullptr;
	float distance = 0.0f;
};

struct OrderCrit
{
	bool operator()(const HitGameObject* Obj_1, const HitGameObject* Obj_2)const
	{
		return Obj_1->distance > Obj_2->distance;
	}
};

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start()override;
	update_status Update(float dt)override;
	bool CleanUp()override;
	bool LoadSettings(Config* data)override;
	bool SaveSettings(Config* data)const override;

	void OnResize(int width, int height);

	void Look(const vec& Position, const vec& Reference, bool RotateAroundReference = false);
	void LookAt(const vec &Spot);
	void Move(const vec &Movement);
	void FitCamera(const AABB& boundingBox);
	vec GetMovementFactor();

	GameObject* CheckMousePick();
	void fillHitGameObjects(GameObject* current, std::priority_queue<HitGameObject*, std::vector<HitGameObject*>, OrderCrit>& gameObjects, LineSegment ray);
	GameObject* checkCloserGameObjects(std::priority_queue<HitGameObject*, std::vector<HitGameObject*>, OrderCrit>& queue, LineSegment ray, float distance = -1);
	float hitsTriangle(GameObject* gameObject, LineSegment ray);
public:
	
	vec X, Y, Z, Position, Reference;

	float cameraSpeed = 0;
	float mouseSensitivity = 0;
	float wheelSensitivity = 0;
	float zoomDistance = 0;
	AABB BBtoLook;

	C_Camera* camera = nullptr;

private:
	mat4x4 ViewMatrix, ViewMatrixInverse;
	bool cameraLookingAtSelectedGameObject;
};