#include "Application.h"
#include "ModuleScene.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Gui";

	root = new GameObject();
	root->name = "Root";

	gameobject1 = CreateGameObject("first child");

	gameobject2 = CreateGameObject("second child");

	gameobject3 = CreateGameObject("third child", gameobject1);
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

GameObject* ModuleScene::CreateGameObject(std::string name, GameObject* parent)
{
	GameObject* newGameObject = nullptr;
	newGameObject = new GameObject();

	newGameObject->name = name;

	if (parent == nullptr)
		AddChild(newGameObject, root);	
	else
		AddChild(newGameObject, parent);

	return newGameObject;
}

void ModuleScene::AddChild(GameObject* child, GameObject* parent)
{
	if (parent == nullptr)
		parent = root;
	else
		parent->childs.push_back(child);

	child->parent = parent;
}

void ModuleScene::DrawGameObjects(GameObject* gameObject, GameObject* root)
{
	if (gameObject != root)
		gameObject->Draw();
	

	for (uint i = 0; i < gameObject->childs.size(); i++)
	{
		DrawGameObjects(gameObject, root);
	}	
}

GameObject* ModuleScene::GetRoot()
{
	return root;
}
