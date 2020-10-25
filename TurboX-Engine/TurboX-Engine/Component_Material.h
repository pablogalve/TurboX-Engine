#ifndef __COMPONENT_MATERIAL_H_
#define __COMPONENT_MATERIAL_H_

#include "Component.h"

class C_Material : public Component {
public:
	C_Material(Component::Type type);
	~C_Material();
};
#endif // !__COMPONENT_MATERIAL_H_
