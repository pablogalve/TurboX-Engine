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

	void Update();
	Component* CreateComponent(Component::Type type);
	Component* GetComponent(Component::Type type);
	void Draw();

	void ChangeName(std::string _name);
public:	
	std::string name;
	vector<Component*> components;
	vector<GameObject*> childs;
	GameObject* parent = NULL;
	C_Mesh* mesh = NULL;
	C_Material* material = NULL;

	bool Get_IsSelected();
	void Select();
	void Unselect();

	
private:
	bool active;	
	bool is_selected;
};

#endif //!__GAMEOBJECT_H__