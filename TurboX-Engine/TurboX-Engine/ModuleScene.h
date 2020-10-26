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

	GameObject* CreateGameObject();
	void AddChild(GameObject* parent, GameObject* child);

	GameObject* GetRoot();

public:
	GameObject* gameobject1;
	GameObject* gameobject2;

private:
	GameObject* root;
};

#endif
