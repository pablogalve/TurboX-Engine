#include "Application.h"
#include "ModuleScene.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Gui";

	root = new GameObject();
	root->name = "Options";

	gameobject1 = new GameObject();
	gameobject1->name = "first child";

	gameobject2 = new GameObject();
	gameobject2->name = "second child";

	AddChild(root, gameobject1);
	AddChild(root, gameobject2);
}

ModuleScene::~ModuleScene()
{}

bool ModuleScene::Start()
{
	bool ret = true;

	return ret;
}

update_status ModuleScene::PreUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt)
{

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	bool ret = true;

	delete root;

	return ret;
}

GameObject* ModuleScene::CreateGameObject()
{
	GameObject* newGameObject = nullptr;



	return newGameObject;
}

void ModuleScene::AddChild(GameObject* parent, GameObject* child)
{
	parent->childs.push_back(child);

	child->parent = parent;
}

GameObject* ModuleScene::GetRoot()
{
	return root;
}
