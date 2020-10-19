#include "Hierarchy.h"

Hierarchy::Hierarchy()
{
}

Hierarchy::~Hierarchy()
{
}

void Hierarchy::Draw()
{
	ImGui::Begin("Hierarchy");

	ImGui::End();
}

void Hierarchy::SetShowWindow()
{
	showWindow = !showWindow;
}
