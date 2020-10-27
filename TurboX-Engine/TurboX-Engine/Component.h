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

public:
	GameObject* owner;

private:
	bool active;
};

#endif // !__COMPONENT_H_
