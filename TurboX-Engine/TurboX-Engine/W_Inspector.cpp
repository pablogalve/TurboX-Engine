#include "W_Inspector.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "MathGeoLib/MathGeoLib.h"
#include "GameObject.h"
W_Inspector::W_Inspector()
{
}

W_Inspector::~W_Inspector()
{
}

void W_Inspector::Draw()
{
	ImGui::Begin("Inspector");

	if (App->editor->hierarchy_window->selectedGameObjects.size() == 1) {
				
		GameObject* gameObject = App->editor->hierarchy_window->selectedGameObjects[0];

		C_Transform* transform = (C_Transform*)gameObject->GetComponent(Component::Type::Transform);
		
		ImVec4 yellow(1.0f, 0.8f, 0.0f, 1.0f);

		if(gameObject->mesh != nullptr)
			ImGui::Checkbox("Enabled", &gameObject->mesh->active); ImGui::SameLine();
		
		strcpy(nameBuffer, gameObject->name.c_str());

		if(ImGui::InputText(" ", nameBuffer, IM_ARRAYSIZE(nameBuffer)))
		{
			gameObject->name.assign(nameBuffer);
		}

		if (ImGui::CollapsingHeader("Transform") && transform != nullptr)
		{
			float3 pos = transform->GetPosition();
			float3 scale = transform->GetScale();
			float3 rotation = transform->GetEulerRotation();

			ImGui::Columns(4, "Transform");
			
			ImGui::NextColumn();
			ImGui::Text("X"); ImGui::NextColumn();
			ImGui::Text("Y"); ImGui::NextColumn();
			ImGui::Text("Z"); ImGui::NextColumn();
			ImGui::Separator();

			// Position
			ImGui::AlignTextToFramePadding();
			ImGui::Text("Position"); ImGui::NextColumn();
			ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
			ImGui::DragFloat("##PositionX", &pos.x, 0, 0.f, 0.f, "%.2f"); ImGui::NextColumn();

			ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
			ImGui::DragFloat("##PositionY", &pos.y, 0, 0.f, 0.f, "%.2f"); ImGui::NextColumn();

			ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
			ImGui::DragFloat("##PositionZ", &pos.z, 0, 0.f, 0.f, "%.2f"); ImGui::NextColumn();

			// Rotation
			ImGui::AlignTextToFramePadding();
			ImGui::Text("Rotation"); ImGui::NextColumn();
			ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
			ImGui::DragFloat("##RotationX", &rotation.x, 0, 0.f, 0.f, "%.2f"); ImGui::NextColumn();

			ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
			ImGui::DragFloat("##RotationY", &rotation.y, 0, 0.f, 0.f, "%.2f"); ImGui::NextColumn();

			ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
			ImGui::DragFloat("##RotationZ", &rotation.z, 0, 0.f, 0.f, "%.2f"); ImGui::NextColumn();

			// Scale
			ImGui::AlignTextToFramePadding();
			ImGui::Text("Scale"); ImGui::NextColumn();
			ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
			ImGui::DragFloat("##ScaleX", &scale.x, 0, 0.f, 0.f, "%.2f"); ImGui::NextColumn();

			ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
			ImGui::DragFloat("##ScaleY", &scale.y, 0, 0.f, 0.f, "%.2f"); ImGui::NextColumn();

			ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
			ImGui::DragFloat("##ScaleZ", &scale.z, 0.05f, 0.f, 0.f, "%.2f"); ImGui::NextColumn();
			
			ImGui::Columns(1);
		}

		
		C_Mesh* mesh = (C_Mesh*)gameObject->GetComponent(Component::Type::Mesh);

		if(ImGui::CollapsingHeader("Mesh") && mesh != nullptr)
		{
			ImGui::Checkbox("Active", &mesh->active);

			ImGui::Text("Index: "); ImGui::SameLine();
			ImGui::TextColored(yellow, "%u", mesh->num_index);
			ImGui::Text("Normals: "); ImGui::SameLine();
			ImGui::TextColored(yellow, "%u", mesh->num_normals);
			ImGui::Text("Vertices: "); ImGui::SameLine();
			ImGui::TextColored(yellow, "%u", mesh->num_vertex);
			ImGui::Text("Tex Coords: "); ImGui::SameLine();
			ImGui::TextColored(yellow, "%u", mesh->num_texcoords);

			ImGui::Checkbox("Vertex Normals:", &mesh->vertex_normals_active);
			ImGui::Checkbox("Face Normals:", &mesh->face_normals_active);
		}

		C_Material* material = (C_Material*)gameObject->GetComponent(Component::Type::Material);

		if (ImGui::CollapsingHeader("Material") && material != nullptr)
		{
			ImGui::Checkbox("Active ", &material->active);
			ImGui::Text("File Path: "); ImGui::SameLine();
			ImGui::TextColored(yellow, material->GetMaterialPath().c_str());
			ImGui::Text("Widht: "); ImGui::SameLine();
			ImGui::TextColored(yellow, "%u", material->Width);
			ImGui::Text("Height: "); ImGui::SameLine();
			ImGui::TextColored(yellow, "%u", material->Height);
			ImGui::Checkbox("Default Texture", &material->defaultTex);

		}
	}	

	ImGui::End();
}

void W_Inspector::SetShowWindow()
{
	showWindow = !showWindow;
}