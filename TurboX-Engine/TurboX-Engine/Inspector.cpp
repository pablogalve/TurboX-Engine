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

		C_Mesh* mesh = (C_Mesh*)gameObject->GetComponent(Component::Type::Mesh);

		if(ImGui::CollapsingHeader("Mesh") && mesh != nullptr)
		{
			ImGui::Checkbox("Active", &mesh->active);

			ImGui::Text("Index: %u", mesh->num_index);
			ImGui::Text("Normals: %u", mesh->num_normals);
			ImGui::Text("Vertices: %u", mesh->num_vertex);
			ImGui::Text("Tex Coords: %u", mesh->num_texcoords);
		}

		C_Material* material = (C_Material*)gameObject->GetComponent(Component::Type::Material);

		if (ImGui::CollapsingHeader("Material") && material != nullptr)
		{
			ImGui::Checkbox("Active", &material->active);
			ImGui::Text("File Path: "); ImGui::SameLine();
			ImVec4 yellow(1.0f, 0.8f, 0.0f, 1.0f);
			ImGui::TextColored(yellow, material->GetMaterialPath().c_str());
		}
	}	

	ImGui::End();
}

void Inspector::SetShowWindow()
{
	showWindow = !showWindow;
}