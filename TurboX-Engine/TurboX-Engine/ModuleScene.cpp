#include "Application.h"
#include "ModuleScene.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "W_Hierarchy.h"
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

	root = CreateGameObject("Root");
	//baker_house = CreateGameObject("Baker House", "Assets/Models/BakerHouse.fbx", "Assets/Textures/Baker_house.png");	
	//airplane = CreateGameObject("Airplane", "Assets/Models/airplane.fbx", "Assets/Textures/airplane.dds");
	street = CreateGameObject("Street", "Assets/Models/street/street2.fbx");

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

	delete baker_house;
	delete airplane;
	delete street;

	delete root;

	return ret;
}

GameObject* ModuleScene::CreateGameObject(std::string name, char* mesh_path, char* texture_path, GameObject* parent)
{
	GameObject* newGameObject = nullptr;
	newGameObject = new GameObject();
	newGameObject->ChangeName(name);

	// Transform
	newGameObject->CreateComponent(Component::Type::Transform);

	// Texture
	if (texture_path != nullptr) {
		newGameObject->CreateComponent(Component::Type::Material);
		newGameObject->material->LoadTexture(texture_path);
	}

	// Mesh
	if (mesh_path != nullptr) {
		newGameObject->CreateComponent(Component::Type::Mesh);
		newGameObject->mesh->LoadMesh(mesh_path, newGameObject);
	}	

	return newGameObject;
}

void ModuleScene::DestroyGameObject(GameObject* selectedGameObject)
{
	if (selectedGameObject->GetToDelete())
	{
		selectedGameObject->components.clear();

		for (int i = 0; i < root->childs.size(); i++)
		{	
			if (root->childs[i]->childs.empty() == false)
			{
				for (size_t j = 0; j < root->childs[i]->childs.size(); j++)
				{
					if (root->childs[i]->childs[j] == selectedGameObject)
					{
						root->childs[i]->childs.erase(root->childs[i]->childs.begin() + j);
					}
				}
			}	
			if (root->childs[i] == selectedGameObject)
			{
				root->childs.erase(root->childs.begin() + i);
			}
		}

		for (int i = 0; i < App->editor->hierarchy_window->selectedGameObjects.size(); i++)
		{
			/*for (int j = 0; j < App->editor->hierarchy_window->selectedGameObjects[i]->childs.size(); j++)
			{
				if (App->editor->hierarchy_window->selectedGameObjects[i]->childs[j] == selectedGameObject)
				{
					App->editor->hierarchy_window->selectedGameObjects[i]->childs.erase(App->editor->hierarchy_window->selectedGameObjects[i]->childs.begin() + j);
				}
			}*/

			if (App->editor->hierarchy_window->selectedGameObjects[i] == selectedGameObject)
			{
				App->editor->hierarchy_window->selectedGameObjects.erase(App->editor->hierarchy_window->selectedGameObjects.begin() + i);
			}

		}
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
