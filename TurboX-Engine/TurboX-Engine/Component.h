#ifndef __COMPONENT_H_
#define __COMPONENT_H_

#include "Globals.h"
#include "Config_JSON.h"

class GameObject;

class Component {
public:
	enum class Type{
		None,
		Transform,
		Mesh,
		Material,
		Camera,
		Light
	};
public:
	Component(Type type, GameObject* owner);
	~Component();

	virtual void Enable();
	virtual void Update();
	virtual void Disable();
	virtual Component::Type GetComponentType();

	virtual bool Save(Config* data);

public:
	GameObject* owner;
	bool active = true;

protected:
	uint component_UUID;
};

#endif // !__COMPONENT_H_
