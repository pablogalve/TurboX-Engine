#include "Resources.h"

Resources::Resources()
{
}

Resources::~Resources()
{
}

void Resources::Draw()
{
	ImGui::Begin("Resources");

	ImGui::End();
}

void Resources::SetShowWindow()
{
	showWindow = !showWindow;
}
