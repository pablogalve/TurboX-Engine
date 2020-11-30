#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
#include <vector>

#include "Component_Mesh.h"
#include "Component_Transformation.h"
#include "Component_Material.h"
#include "Component.h"

using namespace std;

class GameObject {
public:
	GameObject();
	~GameObject();

	Component* CreateComponent(Component::Type type);
	void DestroyComponent();
	Component* GetComponent(Component::Type type);
	void Draw();

	void ChangeName(std::string _name);

	void DeleteGameObject() { to_delete = true; }
	bool GetToDelete() { return to_delete; };

	void SetParent(GameObject* parent);
	void AddChildren(GameObject* child);

public:	
	std::string name;
	vector<Component*> components;
	vector<GameObject*> childs;
	vector<GameObject*> game_objects;
	GameObject* parent;
	C_Mesh* mesh;
	C_Material* material;
	C_Transform* transform;

	bool Get_IsSelected();
	void Select();
	void Unselect();
public:
	bool active;	
	bool is_selected;
	bool to_delete;
};

#endif //!__GAMEOBJECT_H__