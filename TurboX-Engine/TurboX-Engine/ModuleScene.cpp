#include "Application.h"
#include "ModuleScene.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Gui";
}

ModuleScene::~ModuleScene()
{}

bool ModuleScene::Start()
{
	bool ret = true;

	root = new GameObject();
	root->ChangeName("Root");	

	new_gameObject = new GameObject();
	new_gameObject->CreateComponent(Component::Type::Mesh);
	new_gameObject->CreateComponent(Component::Type::Transform);
	new_gameObject->CreateComponent(Component::Type::Material);
	new_gameObject->material->LoadTexture("Assets/Baker_house.png");
	new_gameObject->mesh->LoadMesh("Assets/BakerHouse.fbx");	

	gameobject1 = new GameObject();
	gameobject1->CreateComponent(Component::Type::Mesh);
	gameobject1->CreateComponent(Component::Type::Transform);
	//gameobject1->CreateComponent(Component::Type::Material);
	gameobject1->mesh->LoadMesh("Assets/cottage_fbx.fbx");
	//gameobject1->material->LoadTexture("Assets/Baker_house.png");

	root->childs.push_back(new_gameObject);
	root->childs.push_back(gameobject1);

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

update_status ModuleScene::PostUpdate(float dt)
{
	DrawGameObjects(GetRoot(), GetRoot());

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
	if (parent == nullptr) {
		parent = root;
	}
	else
		parent->childs.push_back(child);

	child->parent = parent;
}

void ModuleScene::DrawGameObjects(GameObject* gameObject, GameObject* root)
{
	bool drawAgain = true;

	if (gameObject != root)
		gameObject->Draw();
	else
		drawAgain = true;
	
	if (drawAgain)
	{
		for (uint i = 0; i < gameObject->childs.size(); i++)
		{
			DrawGameObjects(gameObject->childs[i], root);
		}
	}
}

GameObject* ModuleScene::GetRoot()
{
	return root;
}
