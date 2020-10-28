#ifndef __COMPONENT_H_
#define __COMPONENT_H_

#include "Globals.h"

class GameObject;

class Component {
public:
	enum class Type{
		None,
		Transform,
		Mesh,
		Material,
		Light
	};
public:
	Component(Type type, GameObject* owner);
	~Component();

	virtual void Enable();
	virtual void Update();
	virtual void Disable();
	virtual Component::Type GetComponentType();

public:
	GameObject* owner;
	bool active = true;
};

#endif // !__COMPONENT_H_
