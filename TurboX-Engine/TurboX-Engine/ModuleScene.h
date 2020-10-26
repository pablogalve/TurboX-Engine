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
	bool CleanUp();

	GameObject* CreateGameObject(std::string name, GameObject* parent = nullptr);
	void AddChild(GameObject* child, GameObject* parent = nullptr);

	void DrawGameObjects(GameObject* gameObject, GameObject* root);

	GameObject* GetRoot();

public:
	GameObject* gameobject1;
	GameObject* gameobject2;
	GameObject* gameobject3;

private:
	GameObject* root;
};

#endif
