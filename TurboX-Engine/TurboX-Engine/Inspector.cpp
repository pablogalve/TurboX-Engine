#include "Inspector.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "MathGeoLib/MathGeoLib.h"
#include "GameObject.h"
Inspector::Inspector()
{
}

Inspector::~Inspector()
{
}

void Inspector::Draw()
{
	ImGui::Begin("Inspector");

	if (App->editor->hierarchy_window->selectedGameObjects.size() == 1) {
		
		
		GameObject* gameObject = App->editor->hierarchy_window->selectedGameObjects[0];

		C_Transform* transform = (C_Transform*)gameObject->GetComponent(Component::Type::Transform);

		
		if (ImGui::CollapsingHeader("Transform") && transform != nullptr)
		{
			float3 pos = transform->GetPosition();
			float3 scale = transform->GetScale();
			float3 rotation = transform->GetEulerRotation();

			if (ImGui::InputFloat3("Position", (float*)&pos))
			{
				
			}

			if (ImGui::InputFloat3("Rotation", (float*)&rotation))
			{
				
			}

			if (ImGui::InputFloat3("Scale", (float*)&scale))
			{
				
			}
		}
	}	

	ImGui::End();
}

void Inspector::SetShowWindow()
{
	showWindow = !showWindow;
}