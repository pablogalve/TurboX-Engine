#include "Inspector.h"

Inspector::Inspector()
{
}

Inspector::~Inspector()
{
}

void Inspector::Draw()
{
	ImGui::Begin("Inspector");

	ImGui::End();
}

void Inspector::SetShowWindow()
{
	showWindow = !showWindow;
}