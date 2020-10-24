#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Component.h"
#include <string>
#include <vector>
using namespace std;

class GameObject {
public:
	GameObject();
	~GameObject();

	void Update();
	Component* CreateComponent(Component::Type type);

public:	
	std::string name;
	vector<Component*> components;
private:
	bool active;
};

#endif //!__GAMEOBJECT_H__