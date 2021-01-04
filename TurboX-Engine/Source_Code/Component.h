#ifndef __COMPONENT_H_
#define __COMPONENT_H_

#include "Globals.h"
#include "Config_JSON.h"

class GameObject;
class Resource;

class Component {
public:
	enum Type{
		None = 0,
		Transform,
		Mesh,
		Material,
		Camera,
		Light,
		ParticleSystem,
		Billboard
	};
public:
	Component(Type type, GameObject* owner);
	~Component();

	virtual void Enable();
	virtual void Update();
	virtual void Disable();
	virtual Component::Type GetComponentType();

	virtual bool Save(Config* data);
	virtual bool Load(Config* data);

	virtual void SetResource(uint resource) {};

	virtual Resource* GetResource() const;
	uint GetResourceUUID()const { return component_UUID; }

protected:
	uint component_UUID = 0;
public:
	GameObject* owner;
	bool active = true;

};

#endif // !__COMPONENT_H_
