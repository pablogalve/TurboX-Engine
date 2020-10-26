#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Component_Mesh.h"
#include <string>
#include <vector>
using namespace std;

class GameObject {
public:
	GameObject();
	~GameObject();

	void Update();
	Component* CreateComponent(Component::Type type);

	void Draw();

	void ChangeName(std::string _name);
public:	
	std::string name;
	vector<Component*> components;
	vector<GameObject*> childs;
	GameObject* parent = NULL;
	C_Mesh* mesh = NULL;
private:
	bool active;	
};

#endif //!__GAMEOBJECT_H__