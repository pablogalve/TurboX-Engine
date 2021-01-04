#include "Component_Billboard.h"
#include "ModuleResources.h"
#include "Resource.h"
#include "Application.h"
#include "GameObject.h"
#include "ModuleCamera3D.h"
#include "Libraries\glew\glew.h"
#include "Libraries\SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
C_Billboard::C_Billboard(Component::Type type, GameObject* owner) : Component(type, owner)
{
	this->owner = owner;
	billboard_alignment = SCREEN_ALIGNED;
	res_mesh = App->resources->GetBillboard();
	res_texture = nullptr;
	transform = new C_Transform(Component::Type::Billboard);
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

}

void C_Billboard::Draw(Color color)
{

	FaceCamera();

	if (owner->particle_system != nullptr)
	{
		if (owner->particle_system->particle_material != nullptr)
		{
			glColor4f(color.r, color.g, color.b, color.a);

			glEnable(GL_BLEND);
			glDisable(GL_DEPTH_TEST);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			if (owner->particle_system->particle_material->GetResourceTexture() != nullptr && owner->particle_system->particle_material->HasTexture())
				glBindTexture(GL_TEXTURE_2D, owner->particle_system->particle_material->GetTexID());
			//else
				//glColor4f(mat->color.r, mat->color.g, mat->color.b, mat->color.a);
		}
	}

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