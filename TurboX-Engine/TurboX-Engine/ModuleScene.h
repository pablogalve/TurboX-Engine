#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "GameObject.h"
#include "MathGeoLib/Math/Quat.h"
#include "MathGeoLib/Math/float3.h"

class ModuleScene : public Module
{
public:

	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	GameObject* CreateGameObject(std::string name, float3 position = { 0,0,0 }, Quat rotation = {0,0,0,1}, float3 scale = { 1,1,1 }, GameObject* parent = nullptr, char* mesh_path = nullptr, char* texture_path = nullptr);
	void DestroyGameObject(GameObject* selectedGameObject);
	void AddChild(GameObject* child, GameObject* parent = nullptr);

	void DrawGameObjects(GameObject* gameObject, GameObject* root);

	GameObject* GetRoot();
	GameObject* AddGameObject(const char* name);
	GameObject* AddGameObject(const char* name, GameObject* parent);


public:
	GameObject* baker_house;
	GameObject* airplane;
	GameObject* street;
	GameObject* root;
};

#endif