#ifndef __COMPONENT_BILLBOARD_H__
#define __COMPONENT_BILLBOARD_H__

#include "Component.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include "Component_Camera.h"
#include "Component_Transformation.h"
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

	Component::Type GetComponentType() override;
	void Update() override;
	void Draw();
	void FaceCamera();

	void SetAlignment(Billboarding_Alignment new_alignment);
	std::string GetAlignmentText();
private:
	void ScreenAlign();
	void WorldAlign();
	void AxisAlign();
public:
	C_Transform* transform;
	ResourceMesh* res_mesh;

	float3 pos;
private:
	Billboarding_Alignment billboard_alignment;
	ResourceTexture* res_texture;	

};
#endif //!__COMPONENT_BILLBOARD_H__