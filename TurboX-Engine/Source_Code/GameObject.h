#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
#include <vector>

#include "Component_Mesh.h"
#include "Component_Transformation.h"
#include "Component_Material.h"
#include "Component_Camera.h"
#include "Component_ParticleSystem.h"
#include "Component_Billboard.h"
#include "Component.h"
#include "Config_JSON.h"
#include "ParticleModule.h"
#include "Libraries/MathGeoLib/Algorithm/Random/LCG.h"

using namespace std;

class GameObject {
public:
	GameObject();
	~GameObject();

	Component* CreateComponent(Component::Type type);
	void DestroyComponent(Component::Type type);
	Component* GetComponent(Component::Type type);
	void Draw();
	void DrawBB(const AABB& BB, vec color) const;

	void ChangeName(std::string _name);

	void RecalculateBB();

	void SetParent(GameObject* parent);
	void AddChildren(GameObject* child);
	void setSelected(bool selected);
	void setChildSelected(bool selected);
	void DestroyChildren(GameObject* toRemove);

	uint GenerateUUID();
	uint GetUUID();
	uint GetParentUUID();

	bool Get_IsSelected();
	void Select();
	void Unselect();

	bool Update();
	bool Save(Config* data);
	bool Load(Config* data);

	void GetComponents(Component::Type type, std::vector<Component*>& comp);
	C_Material* GetComponentMaterial(uint UUID);

	void CreateCustomParticleSystem(ParticleModule::Type type, float3 position = { -1,-1,-1 });
public:	
	std::string name;
	vector<Component*> components;
	vector<GameObject*> childs;
	GameObject* parent;
	C_Mesh* mesh;
	C_Material* material;
	C_Transform* transform;
	C_Camera* camera;
	C_ParticleSystem* particle_system;
	C_Billboard* billboard;

	AABB boundingBox;

	bool active;	
	bool is_selected;
	bool to_delete;
	bool culling;
	bool child_selected;
	bool isStatic;

private:
	uint parentUUID;
	uint UUID;
};

#endif //!__GAMEOBJECT_H__