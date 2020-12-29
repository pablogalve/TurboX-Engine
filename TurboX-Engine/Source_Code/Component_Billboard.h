#ifndef __COMPONENT_BILLBOARD_H__
#define __COMPONENT_BILLBOARD_H__

#include "Component.h"
class GameObject;

class C_Billboard : public Component {
public:
	enum BillboardingTypes {
		SCREEN_ALIGNED,
		WORLD_ALIGNED,
		AXIS_ALIGNED
	};

	C_Billboard(Component::Type type, GameObject* owner);
	~C_Billboard();
};

#endif //!__COMPONENT_BILLBOARD_H__