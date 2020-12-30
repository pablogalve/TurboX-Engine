#include "Component_Billboard.h"

C_Billboard::C_Billboard(Component::Type type, GameObject* owner) : Component(type, owner)
{
	this->owner = owner;
	billboard_alignment = SCREEN_ALIGNED;
}

C_Billboard::~C_Billboard()
{
}

void C_Billboard::Update()
{
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
	case 0:
		ret_word = "Screen Aligned";
		return ret_word;
		break;
	case 1:
		ret_word = "World Aligned";
		return ret_word;
		break;
	case 2:
		ret_word = "Axis Aligned";
		return ret_word;
		break;
	default:
		ret_word = "None";
		return ret_word;
		break;
	}
}
