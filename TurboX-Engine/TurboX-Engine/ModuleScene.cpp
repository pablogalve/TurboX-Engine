#include "Application.h"
#include "ModuleScene.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "W_Hierarchy.h"
#include "ModuleEditor.h"
#include "ModuleInput.h"
#include "ModuleCamera3D.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Scene";
	root = new GameObject();
	root->name = "root";
	selected_GO = nullptr;
	guizmoOperation = ImGuizmo::NO_OPERATION;
}

ModuleScene::~ModuleScene()
{}

bool ModuleScene::Start()
{
	bool ret = true;

	ImGuizmo::Enable(false);	

	AddCamera();

	return ret;
}

update_status ModuleScene::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt)
{
	if (App->scene->selected_GO != nullptr)
	{
		if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_IDLE)
		{
			if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
			{
				guizmoOperation = ImGuizmo::NO_OPERATION;
			}
			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			{
				guizmoOperation = ImGuizmo::TRANSLATE;
			}
			if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
			{
				guizmoOperation = ImGuizmo::ROTATE;
			}
			if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT)
			{
				guizmoOperation = ImGuizmo::SCALE;
			}
		}
	}

	FrustumCulling(GetRoot(), GetRoot());

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

GameObject* ModuleScene::CreateGameObject(std::string name, float3 position, Quat rotation, float3 scale, GameObject* parent, char* mesh_path, char* texture_path)
{
	GameObject* newGameObject = nullptr;
	newGameObject = new GameObject();
	newGameObject->ChangeName(name);

	if (newGameObject != nullptr)
	{
		if (parent != nullptr) {
			App->scene->AddChild(newGameObject, parent);
		}		
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

void ModuleScene::FrustumCulling(GameObject* gameObject, GameObject* root)
{
	for (std::vector<GameObject*>::iterator it_c = cameras.begin(); it_c != cameras.end(); it_c++)
	{
		GameObject* sceneCamera = (*it_c);

		if (sceneCamera != nullptr)
		{
			if (sceneCamera->camera->ContainsAABB(gameObject->boundingBox))
			{
				gameObject->culling = true;
			}
			else
			{
				gameObject->culling = false;
			}

			for (uint i = 0; i < gameObject->childs.size(); i++)
			{
				FrustumCulling(gameObject->childs[i], root);
			}

		}
	}
}

GameObject* ModuleScene::GetRoot()
{
	return root;
}

GameObject* ModuleScene::AddGameObject(const char* name)
{
	GameObject* ret = new GameObject();
	ret->name = name;
	ret->parent = root;
	root->childs.push_back(ret);

	return ret;
}

GameObject* ModuleScene::AddGameObject(const char* name, GameObject* parent)
{
	GameObject* ret = new GameObject();
	ret->name = name;
	ret->parent = parent;
	parent->childs.push_back(ret);

	return ret;
}

void ModuleScene::AddCamera()
{
	GameObject* newGameObject = new GameObject();
	newGameObject->name = "Camera";
	newGameObject->SetParent(root);
	newGameObject->isStatic = false;

	float3 pos = float3::zero;
	float3 scale = float3::one;
	Quat rot = Quat::identity;

	newGameObject->transform->position = pos;
	newGameObject->transform->scale = scale;
	newGameObject->transform->rotation = rot;
	newGameObject->transform->localMatrix.Set(float4x4::FromTRS(pos, rot, scale));

	newGameObject->CreateComponent(Component::Type::Camera);

	newGameObject->camera->frustum.farPlaneDistance = 100.0f;
	newGameObject->camera->frustum.verticalFov = DEGTORAD * 30.0f;
	newGameObject->camera->setAspectRatio(16.0f / 9.0f);
	newGameObject->camera->RecalculateBB();

	newGameObject->boundingBox = newGameObject->camera->cameraBB;

	cameras.push_back(newGameObject);
}

void ModuleScene::selectGameObject(GameObject* gameObject)
{
	if (selected_GO != nullptr)
		selected_GO->setSelected(false);

	selected_GO = gameObject;
	if (gameObject != nullptr)
		gameObject->setSelected(true);
}

void ModuleScene::DrawGuizmo(ImGuizmo::OPERATION operation)
{
	C_Transform* transform = (C_Transform*)selected_GO->GetComponent(Component::Type::Transform);

	if (transform != nullptr)
	{
		ImGuizmo::Enable(!selected_GO->isStatic);

		if (operation == ImGuizmo::NO_OPERATION)
		{
			ImGuizmo::Enable(false);
		}

		ImVec2 cursorPos = { App->editor->sceneX,App->editor->sceneY };
		ImVec2 windowSize = { App->editor->sceneW,App->editor->sceneH };
		ImGuizmo::SetRect(cursorPos.x, cursorPos.y, windowSize.x, windowSize.y);

		float4x4* ViewMatrix = (float4x4*)App->camera->camera->getViewMatrix();
		float4x4* ProjectionMatrix = (float4x4*)App->camera->camera->getProjectionMatrix();

		ImGuizmo::MODE mode;

		float4x4* GlobalMat;
		GlobalMat = &transform->globalMatrix;

		float3 scale = float3::one;
		float3 pos;
		Quat rot;
		if (operation != ImGuizmo::OPERATION::SCALE)
		{
			GlobalMat->Decompose(pos, rot, scale);
			GlobalMat->Set(float4x4::FromTRS(pos, rot, float3::one));
		}
		GlobalMat->Transpose();

		ImGuizmo::SetOrthographic(false);

		ImGuizmo::Manipulate((float*)ViewMatrix, (float*)ProjectionMatrix, operation, ImGuizmo::LOCAL, (float*)GlobalMat, NULL, NULL);
		GlobalMat->Transpose();

		if (operation != ImGuizmo::OPERATION::SCALE)
		{
			float3 oneScale;
			GlobalMat->Decompose(pos, rot, oneScale);
			GlobalMat->Set(float4x4::FromTRS(pos, rot, scale));
		}

		if (ImGuizmo::IsUsing())
		{
			if (selected_GO->parent != nullptr)
			{
				transform->localMatrix = ((C_Transform*)selected_GO->parent->GetComponent(Component::Type::Transform))->globalMatrix.Inverted() * transform->globalMatrix;

			}
			transform->localMatrix.Decompose(transform->position, transform->rotation, transform->scale);
			selected_GO->RecalculateBB(); //To avoid that the BB laggs to follow object position
			transform->changed = true;
		}
	}
}

bool ModuleScene::LoadSettings(Config* data)
{
	bool ret = true;

	return ret;
}

bool ModuleScene::SaveSettings(Config* data) const
{
	bool ret = true;

	data->AddArray("GameObjects");
	
	//Iterate gameObjects to save them
	for (size_t i = 0; i < root->childs.size(); i++)
	{
		Config gameObjectData;
		root->childs[i]->Save(&gameObjectData);
		data->AddArrayChild(gameObjectData);

		//Save second hierarchy of gameObjects
		for (size_t j = 0; j < root->childs[i]->childs.size(); j++)
		{
			root->childs[i]->childs[j]->Save(&gameObjectData);
			data->AddArrayChild(gameObjectData);
		}
	}

	return ret;
}

uint ModuleScene::GetRandomUUID()
{
	return LCG().Int();
}