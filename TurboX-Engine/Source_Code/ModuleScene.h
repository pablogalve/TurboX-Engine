#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "GameObject.h"
#include "MathGeoLib/MathGeoLib.h"
#include "ImGuizmo/ImGuizmo.h"
#include "Component_Material.h"
#include <vector>

using namespace std;

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

	GameObject* CreateGameObject(std::string name, float3 position = { 0,0,0 }, Quat rotation = {0,0,0,1}, float3 scale = { 1,1,1 }, GameObject* parent = nullptr, char* mesh_path = nullptr, char* texture_path = nullptr);
	void DestroyGameObject(GameObject* selectedGameObject);
	void AddChild(GameObject* child, GameObject* parent = nullptr);

	void DrawGameObjects(GameObject* gameObject, GameObject* root);
	void FrustumCulling(GameObject* gameObject, GameObject* root);

	GameObject* GetRoot();
	GameObject* GetGameObjectByUUID(uint UUID) const;	
	GameObject* AddGameObject(const char* name);
	GameObject* AddGameObject(const char* name, GameObject* parent);
	void selectGameObject(GameObject* gameObject);
	void ClearScene();

	void CreateCamera();
	void CreateEmptyGameObject();

	void DrawGuizmo(ImGuizmo::OPERATION operation);

	bool LoadSettings(Config* data)override;
	bool LoadScene(const char* file);
	bool SaveSettings(Config* data)const override;

	uint GetRandomUUID();

private:
	GameObject* GetGameObjectUUIDRecursive(uint UUID, GameObject* go) const;
	void UpdateGameObjects(GameObject* gameObject);

public:
	GameObject* root;

	std::vector<GameObject*> cameras;

	GameObject* selected_GO;

	ImGuizmo::OPERATION guizmoOperation;
	bool inGame;

	std::list<C_Material*> materials;

};

#endif