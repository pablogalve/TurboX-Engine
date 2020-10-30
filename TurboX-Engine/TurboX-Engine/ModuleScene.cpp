#include "Application.h"
#include "ModuleScene.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "Hierarchy.h"
#include "ModuleEditor.h"

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

	baker_house = new GameObject();
	baker_house->CreateComponent(Component::Type::Mesh);
	baker_house->CreateComponent(Component::Type::Transform);
	baker_house->CreateComponent(Component::Type::Material);
	baker_house->material->LoadTexture("Baker_house.png");
	baker_house->mesh->LoadMesh("Assets/BakerHouse.fbx");	

	root->childs.push_back(baker_house);

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

	if(App->editor->hierarchy_window->selectedGameObjects.empty() == false)
		DestroyGameObject(App->editor->hierarchy_window->selectedGameObjects[0]);

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

void ModuleScene::DestroyGameObject(GameObject* selectedGameObject)
{
	if (selectedGameObject->GetToDelete()) {

		selectedGameObject->mesh = nullptr;
		delete selectedGameObject->mesh;
		selectedGameObject->material = nullptr;
		delete selectedGameObject->material;

		for (int i = 0; i < selectedGameObject->childs.size(); ++i)
			delete selectedGameObject->childs[i];

		selectedGameObject->childs.clear();

		for (int i = 0; i < selectedGameObject->components.size(); ++i)
			delete selectedGameObject->components[i];

		selectedGameObject->components.clear();

		selectedGameObject = nullptr;
		delete selectedGameObject;
	}	
}

void ModuleScene::AddChild(GameObject* child, GameObject* parent)
{
	if (parent == nullptr)
		parent = root;
	
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
