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
	
	if (ImGui::CollapsingHeader("Transform"))
	{
		float p[3] = { 0.0f, 0.0f, 0.0f };
		float r[3] = { 0.0f, 0.0f, 0.0f };
		float s[3] = { 0.0f, 0.0f, 0.0f };
		if (ImGui::InputFloat3("Position", p));
		if (ImGui::InputFloat3("Rotation", r));
		if (ImGui::InputFloat3("Scale", s));
	}
	if (ImGui::CollapsingHeader("Mesh"))
	{

	}
	if (ImGui::CollapsingHeader("Material"))
	{

	}

	ImGui::End();
}

void Inspector::SetShowWindow()
{
	showWindow = !showWindow;
}