#include "Application.h"
#include "ModuleScene.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "W_Hierarchy.h"
#include "ModuleEditor.h"
#include "ModuleInput.h"
#include "ModuleCamera3D.h"
#include "ModuleFileSystem.h"
#include "ModuleResources.h"
#include "ModuleSceneLoader.h"
#include "ParticleEmitter.h"
#include "ParticleModule.h"
#include "GameObject.h"
#include <vector>

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Scene";
	root = new GameObject();
	root->name = "root";
	selected_GO = nullptr;
	inGame = false;
	guizmoOperation = ImGuizmo::NO_OPERATION;
}

ModuleScene::~ModuleScene()
{}

bool ModuleScene::Start()
{
	bool ret = true;

	ImGuizmo::Enable(false);	

	CreateCamera(); //Camera created on Application.cpp after LoadEngineNow() 

	
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

	//FrustumCulling(GetRoot(), GetRoot());

	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate(float dt)
{
	DrawGameObjects(GetRoot(), GetRoot());

	UpdateGameObjects(GetRoot());

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		GameObject* newFirework = CreateGameObject("firework");
		newFirework->CreateComponent(Component::Type::ParticleSystem);
		newFirework->particle_system->emitters.push_back(EmitterInstance());
		ParticleEmitter* emitterReference = new ParticleEmitter();
		newFirework->particle_system->emitters.back().owner = (C_ParticleSystem*)newFirework->GetComponent(Component::Type::ParticleSystem);	//Set EmitterInstance's owner
		newFirework->particle_system->emitters.back().Init(emitterReference);
		Firework* firework = new Firework(newFirework);
		newFirework->particle_system->emitters.back().emitter->modules.push_back(firework);
	}

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
		App->scene->AddChild(newGameObject, parent);	

	newGameObject->transform->SetPosition(position);
	newGameObject->transform->SetQuaternionRotation(rotation);
	newGameObject->transform->SetScale(scale);
	newGameObject->transform->changed = true;

	return newGameObject;
}

void ModuleScene::DestroyGameObject(GameObject* GO)
{
	GO->components.clear();

	for (int i = 0; i < root->childs.size(); i++)
	{
		if (root->childs[i]->childs.empty() == false)
		{
			for (size_t j = 0; j < root->childs[i]->childs.size(); j++)
			{
				if (root->childs[i]->childs[j] == GO)
				{
					root->childs[i]->childs.erase(root->childs[i]->childs.begin() + j);
				}
			}
		}
		if (root->childs[i] == GO)
		{
			root->childs.erase(root->childs.begin() + i);
		}
	}

	if (selected_GO == GO)
		selected_GO = nullptr;
	
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

GameObject* ModuleScene::GetGameObjectByUUID(uint UUID) const
{
	GameObject* ret = nullptr;
	ret = GetGameObjectUUIDRecursive(UUID, root);
	return ret;
}

GameObject* ModuleScene::GetGameObjectUUIDRecursive(uint UUID, GameObject* go) const
{
	GameObject* ret = go;
	if (ret->GetUUID() == UUID) {
		return ret;
	}

	for (int i = 0; i < go->childs.size(); i++) {
		ret = go->childs[i];
		ret = GetGameObjectUUIDRecursive(UUID, ret);
		if (ret) {
			return ret;
		}
	}
	return nullptr;
}

void ModuleScene::UpdateGameObjects(GameObject* gameObject)
{
	gameObject->Update();
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

void ModuleScene::CreateCamera()
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

void ModuleScene::CreateEmptyGameObject()
{
	GameObject* newGameObject = new GameObject();
	newGameObject->name = "Empty GameObject";
	newGameObject->SetParent(root);
	newGameObject->isStatic = false;

	float3 pos = float3::zero;
	float3 scale = float3::one;
	Quat rot = Quat::identity;

	newGameObject->transform->position = pos;
	newGameObject->transform->scale = scale;
	newGameObject->transform->rotation = rot;
	newGameObject->transform->localMatrix.Set(float4x4::FromTRS(pos, rot, scale));
}

void ModuleScene::LoadTownScene()
{	
	GameObject* newGameObject;

	newGameObject = App->scene_loader->LoadStreet("Assets/Models/Street environment_V01.FBX");

	float3 pos = float3::zero;
	float3 scale = float3::one;

	newGameObject->transform->SetPosition(pos);
	newGameObject->transform->SetScale(scale);
	newGameObject->transform->SetRotation({ -90,0,0 });
	newGameObject->transform->changed = true;

	//Smoke 1
	float3 smoke1pos = { 24.72, 10.1f, 40.61f };
	GameObject* newSmoke1 = CreateGameObject("Smoke1", smoke1pos);
	newSmoke1->CreateComponent(Component::Type::ParticleSystem);
	newSmoke1->particle_system->emitters.push_back(EmitterInstance());
	//Set Particle Emitter
	ParticleEmitter* emitterReference = new ParticleEmitter();
	newSmoke1->particle_system->emitters.back().owner = (C_ParticleSystem*)newSmoke1->GetComponent(Component::Type::ParticleSystem);	//Set EmitterInstance's owner
	newSmoke1->particle_system->emitters.back().Init(emitterReference);
	newSmoke1->particle_system->particle_material = new C_Material(Component::Type::Material, newSmoke1->parent);
	newSmoke1->particle_system->color.min = {0.3, 0.3, 0.3, 1.0};
	newSmoke1->particle_system->size.min = 0.5f;
	newSmoke1->particle_system->speed.min = 0.3f;
	newSmoke1->particle_system->dirVariation = 40.0f;
	newSmoke1->particle_system->lifetime.min = 10.0f;
	newSmoke1->particle_system->emitters[0].UpdateParticleReference();
	//Set Resource
	std::string resourceName1 = "smoke1";
	Resource* resourceSmoke1 = App->resources->GetResourceByName(&resourceName1);
	if (resourceSmoke1 != nullptr) newSmoke1->particle_system->particle_material->SetResource(resourceSmoke1->GetUUID());

	//Smoke 2
	float3 smoke2pos = { -30.36f, 7.11f, -33.78f };
	GameObject* newSmoke2 = CreateGameObject("Smoke2", smoke2pos);
	newSmoke2->CreateComponent(Component::Type::ParticleSystem);
	newSmoke2->particle_system->emitters.push_back(EmitterInstance());
	newSmoke2->particle_system->emitters.back().owner = (C_ParticleSystem*)newSmoke2->GetComponent(Component::Type::ParticleSystem);	//Set EmitterInstance's owner
	newSmoke2->particle_system->emitters.back().Init(emitterReference);
	newSmoke2->particle_system->particle_material = new C_Material(Component::Type::Material, newSmoke2->parent);
	newSmoke2->particle_system->color.min = { 0.3, 0.3, 0.3, 1.0 };
	newSmoke2->particle_system->size.min = 0.5f;
	newSmoke2->particle_system->speed.min = 0.3f;
	newSmoke2->particle_system->dirVariation = 40.0f;
	newSmoke2->particle_system->lifetime.min = 10.0f;
	newSmoke2->particle_system->emitters[0].UpdateParticleReference();
	//Set Resource
	std::string resourceName2 = "smoke1";
	Resource* resourceSmoke2 = App->resources->GetResourceByName(&resourceName2);
	if (resourceSmoke2 != nullptr) newSmoke2->particle_system->particle_material->SetResource(resourceSmoke2->GetUUID());
}

void ModuleScene::selectGameObject(GameObject* gameObject)
{
	if (selected_GO != nullptr)
		selected_GO->setSelected(false);

	selected_GO = gameObject;
	if (gameObject != nullptr)
		gameObject->setSelected(true);
}

void ModuleScene::ClearScene()
{
	MY_LOG("Clearing scene");
	for (int i = root->childs.size() - 1; i >= 0; i--) {
		root->DestroyChildren(root->childs[i]);
	}
	for (int i = root->components.size() - 1; i >= 0; i--) {
		root->DestroyComponent(root->components[i]->GetComponentType());
	}
	for (size_t i = 0; i < cameras.size(); i++)
	{
		cameras[i] = nullptr;
	}
	//TODO: Deselect all the selected gameObjects
}

void ModuleScene::DrawGuizmo(ImGuizmo::OPERATION operation)
{
	C_Transform* transform = (C_Transform*)selected_GO->GetComponent(Component::Type::Transform);

	if (transform != nullptr)
	{
		ImGuizmo::Enable(true);

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
	
	//Load gameObjects data

	MY_LOG("llega");

	return ret;
}

bool ModuleScene::LoadGameObjects(GameObject* gameObject)
{
	bool ret = true;



	return ret;
}

bool ModuleScene::LoadScene(const char* file)
{	
	ClearScene();
	char* buffer = nullptr;
	const char* fileName = nullptr;
	if (file == nullptr) {
		fileName = DEFAULT_SCENE_FILE;
	}
	else {
		fileName = file;
	}
	uint size = App->file_system->readFile(fileName, &buffer);

	if (size < 0) {
		MY_LOG("Error loading file %s. All data not loaded.", fileName)
			fileName = nullptr;
		RELEASE_ARRAY(buffer);
		return false;
	}
	fileName = nullptr;

	Config conf(buffer);
	RELEASE_ARRAY(buffer);

	Config gameObjectData = conf.GetArray(name.c_str(), 0);
	int gameObjects_num = gameObjectData.GetNumElementsInArray("GameObjects");
	if(gameObjects_num == -1)
		MY_LOG("Warning. No gameObjects detected in the scene.");

	for (int i = 0; i < gameObjects_num; i++) {
		Config elem = gameObjectData.GetArray("GameObjects", i);
		GameObject* go = CreateGameObject("GameObject");
		go->Load(&elem);
	}
	MY_LOG("Loading new scene.");
	RELEASE_ARRAY(buffer);

	return false;
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