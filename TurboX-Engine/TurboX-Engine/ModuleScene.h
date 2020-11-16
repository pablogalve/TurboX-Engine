#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "GameObject.h"

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

	GameObject* CreateGameObject(std::string name, char* mesh_path = nullptr, char* texture_path = nullptr, GameObject* parent = nullptr);
	void DestroyGameObject(GameObject* selectedGameObject);
	void AddChild(GameObject* child, GameObject* parent = nullptr);

	void DrawGameObjects(GameObject* gameObject, GameObject* root);

	GameObject* GetRoot();

public:
	GameObject* baker_house;
	GameObject* airplane;
	GameObject* street;

private:
	GameObject* root;
};

#endif