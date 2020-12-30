#include "Component_Billboard.h"
#include "ModuleResources.h"
#include "Resource.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "glew\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
C_Billboard::C_Billboard(Component::Type type, GameObject* owner) : Component(type, owner)
{
	this->owner = owner;
	billboard_alignment = SCREEN_ALIGNED;
	res_mesh = App->resources->GetBillboard();
	res_texture = nullptr;
	transform = nullptr;
}

C_Billboard::~C_Billboard()
{
}

Component::Type C_Billboard::GetComponentType()
{
	return Component::Type::Billboard;
}

void C_Billboard::Update()
{
	FaceCamera();

	transform->RecalculateMatrix();

	glPushMatrix();
	glMultMatrixf(transform->localMatrix.Transposed().ptr());

	res_mesh->Draw();

	glPopMatrix();
}

void C_Billboard::FaceCamera()
{
	switch (billboard_alignment)
	{
	case Billboarding_Alignment::SCREEN_ALIGNED:
		ScreenAlign();
		break;
	case Billboarding_Alignment::WORLD_ALIGNED:
		WorldAlign();
		break;
	case Billboarding_Alignment::AXIS_ALIGNED:
		AxisAlign();
		break;
	default:
		break;
	}
}

void C_Billboard::SetAlignment(Billboarding_Alignment new_alignment)
{
	billboard_alignment = new_alignment;
}

std::string C_Billboard::GetAlignmentText()
{
	std::string ret_word = "";
	switch (billboard_alignment)
	{
	case Billboarding_Alignment::SCREEN_ALIGNED:
		ret_word = "Screen Aligned";
		return ret_word;
		break;
	case Billboarding_Alignment::WORLD_ALIGNED:
		ret_word = "World Aligned";
		return ret_word;
		break;
	case Billboarding_Alignment::AXIS_ALIGNED:
		ret_word = "Axis Aligned";
		return ret_word;
		break;
	default:
		ret_word = "None";
		return ret_word;
		break;
	}
}

void C_Billboard::ScreenAlign()
{
	float3 normal = (App->camera->Position - this->transform->position).Normalized();
	float3 up = App->camera->camera->frustum.up;
	float3 right = normal.Cross(up);

	float3x3 mat = float3x3::identity;
	mat.Set(-right.x, -right.y, -right.z, up.x, up.y, up.z, normal.x, normal.y, normal.z);

	transform->rotation = mat.Inverted().ToQuat();
}

void C_Billboard::WorldAlign()
{
}

void C_Billboard::AxisAlign()
{
}