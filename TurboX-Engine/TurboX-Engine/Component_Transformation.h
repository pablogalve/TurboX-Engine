#ifndef __COMPONENT_TRANSFORMATION_H_
#define __COMPONENT_TRANSFORMATION_H_

#include "Component.h"

class C_Transform : public Component {
public:
	C_Transform(Component::Type type);
	~C_Transform();
};
#endif // !__COMPONENT_TRANSFORMATION_H_
