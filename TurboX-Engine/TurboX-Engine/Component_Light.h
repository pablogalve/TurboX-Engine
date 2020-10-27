#ifndef __COMPONENT_LIGHT_H_
#define __COMPONENT_LIGHT_H_

#include "Component.h"

class C_Light : public Component {
public:
	C_Light(Component::Type type, GameObject* owner);
	~C_Light();

public:

	Component::Type GetComponentType() override;
};
#endif // !__COMPONENT_LIGHT_H_