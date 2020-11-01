#include "W_Resources.h"

W_Resources::W_Resources()
{
}

W_Resources::~W_Resources()
{
}

void W_Resources::Draw()
{
	ImGui::Begin("Resources");

	ImGui::End();
}

void W_Resources::SetShowWindow()
{
	showWindow = !showWindow;
}
