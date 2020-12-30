#ifndef __COMPONENT_BILLBOARD_H__
#define __COMPONENT_BILLBOARD_H__

#include "Component.h"
#include <string>
class GameObject;
class C_Material;

enum Billboarding_Alignment {
	SCREEN_ALIGNED = 0,
	WORLD_ALIGNED,
	AXIS_ALIGNED
};

class C_Billboard : public Component {
public:
	C_Billboard(Component::Type type, GameObject* owner);
	~C_Billboard();

	void Update() override;

	void SetAlignment(Billboarding_Alignment new_alignment);
	std::string GetAlignmentText();
private:
	Billboarding_Alignment billboard_alignment;
};

#endif //!__COMPONENT_BILLBOARD_H__