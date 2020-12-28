#include "W_Inspector.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "MathGeoLib/MathGeoLib.h"
#include "MathGeoLib/Math/float3.h"
#include "GameObject.h"
#include "Resource.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include "ModuleScene.h"
#include "ModuleResources.h"

W_Inspector::W_Inspector()
{
	active = true;
}

W_Inspector::~W_Inspector()
{
}

void W_Inspector::Draw()
{
	ImGui::Begin("Inspector", &active, ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_AlwaysVerticalScrollbar);
	
	GameObject* gameObject = App->scene->selected_GO;

	if (gameObject != nullptr)
	{	
		ImVec4 yellow(1.0f, 0.8f, 0.0f, 1.0f);

		if(gameObject->mesh != nullptr)
			ImGui::Checkbox("Enabled", &gameObject->mesh->active); ImGui::SameLine();
		
		strcpy(nameBuffer, gameObject->name.c_str());

		if(ImGui::InputText(" ", nameBuffer, IM_ARRAYSIZE(nameBuffer)))
		{
			gameObject->name.assign(nameBuffer);
		}

		C_Transform* transform = (C_Transform*)gameObject->GetComponent(Component::Type::Transform);
		if (transform != nullptr) {
			if (ImGui::CollapsingHeader("Transform"))
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
				if (ImGui::DragFloat("##PositionX", &pos.x, 0.05f, 0.f, 0.f, "%.2f"))
				{
					transform->SetPosition(pos);
					transform->changed = true;
				}
				ImGui::NextColumn();

				ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
				if (ImGui::DragFloat("##PositionY", &pos.y, 0.05f, 0.f, 0.f, "%.2f"))
				{
					transform->SetPosition(pos);
					transform->changed = true;
				}
				ImGui::NextColumn();

				ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
				if (ImGui::DragFloat("##PositionZ", &pos.z, 0.05f, 0.f, 0.f, "%.2f"))
				{
					transform->SetPosition(pos);
					transform->changed = true;
				}
				ImGui::NextColumn();

				// Rotation
				ImGui::AlignTextToFramePadding();
				ImGui::Text("Rotation"); ImGui::NextColumn();
				ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);

				if (ImGui::DragFloat("##RotationX", &rotation.x, 0.05f, 0.f, 0.f, "%.2f"))
				{
					transform->SetRotation(rotation);
					transform->changed = true;
				}
				ImGui::NextColumn();

				ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
				if (ImGui::DragFloat("##RotationY", &rotation.y, 0.05f, 0.f, 0.f, "%.2f"))
				{
					transform->SetRotation(rotation);
					transform->changed = true;
				}
				ImGui::NextColumn();

				ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
				if (ImGui::DragFloat("##RotationZ", &rotation.z, 0.05f, 0.f, 0.f, "%.2f"))
				{
					transform->SetRotation(rotation);
					transform->changed = true;
				}
				ImGui::NextColumn();
				// Scale
				ImGui::AlignTextToFramePadding();
				ImGui::Text("Scale"); ImGui::NextColumn();
				ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
				if (ImGui::DragFloat("##ScaleX", &scale.x, 0.05f, 0.f, 0.f, "%.2f"))
				{
					transform->SetScale(scale);
					transform->changed = true;
				}
				ImGui::NextColumn();

				ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
				if (ImGui::DragFloat("##ScaleY", &scale.y, 0.05f, 0.f, 0.f, "%.2f"))
				{
					transform->SetScale(scale);
					transform->changed = true;
				}
				ImGui::NextColumn();

				ImGui::SetNextItemWidth(ImGui::GetWindowWidth() / 5.0f);
				if (ImGui::DragFloat("##ScaleZ", &scale.z, 0.05f, 0.f, 0.f, "%.2f"))
				{
					transform->SetScale(scale);
					transform->changed = true;
				}

				ImGui::NextColumn();
				ImGui::Columns(1);
			}
		}	
		
		C_Mesh* mesh = (C_Mesh*)gameObject->GetComponent(Component::Type::Mesh);
		if (mesh != nullptr) {
			if (ImGui::CollapsingHeader("Mesh"))
			{
				uint n_index = mesh->GetResourceMesh()->num_index;
				uint n_vertex = mesh->GetResourceMesh()->num_vertex;
				uint n_normals = mesh->GetResourceMesh()->num_normals;
				uint n_textureCoord = mesh->GetResourceMesh()->num_textureCoords;

				ImGui::Checkbox("Active", &mesh->active);

				ImGui::Text("Index: "); ImGui::SameLine();
				ImGui::TextColored(yellow, "%u", n_index);
				ImGui::Text("Normals: "); ImGui::SameLine();
				ImGui::TextColored(yellow, "%u", n_normals);
				ImGui::Text("Vertices: "); ImGui::SameLine();
				ImGui::TextColored(yellow, "%u", n_vertex);
				ImGui::Text("Tex Coords: "); ImGui::SameLine();
				ImGui::TextColored(yellow, "%u", n_textureCoord);

				ImGui::Checkbox("Vertex Normals:", &mesh->vertex_normals_active);
				//ImGui::Checkbox("Face Normals:", &mesh->face_normals_active);
			}
		}		

		C_Material* material = (C_Material*)gameObject->GetComponent(Component::Type::Material);
		if(material != nullptr)
		{
			if (ImGui::CollapsingHeader("Material"))
			{
				uint w = material->GetResourceTexture()->width;
				uint h = material->GetResourceTexture()->height;
				uint tex = material->GetResourceTexture()->gpuID;
				uint uuid = material->GetResourceTexture()->GetUUID();
				float windowSize = ImGui::GetWindowContentRegionWidth();

				ImGui::Checkbox("Active ", &material->active);
				ImGui::Text("Resource UUID:: "); ImGui::SameLine();
				ImGui::TextColored(yellow, "%i", uuid);
				ImGui::Text("Widht: "); ImGui::SameLine();
				ImGui::TextColored(yellow, "%u", w);
				ImGui::Text("Height: "); ImGui::SameLine();
				ImGui::TextColored(yellow, "%u", h);
				ImGui::Image((void*)(tex), ImVec2(windowSize, windowSize));
				//ImGui::Checkbox("Default Texture", &material->defaultTex);
			}
		}

		C_Camera* camera = (C_Camera*)gameObject->GetComponent(Component::Type::Camera);
		if (camera != nullptr) {
		if (ImGui::CollapsingHeader("Camera"))
		{
			ImGui::DragFloat("Near Plane", &camera->frustum.nearPlaneDistance, 0.05f, 0.f, 0.f, "%.2f");
			ImGui::DragFloat("Far Plane", &camera->frustum.farPlaneDistance, 0.05f, 0.f, 0.f, "%.2f");

			float aspectRatio = camera->frustum.AspectRatio();
			float fov = camera->frustum.verticalFov * RADTODEG;

			if (ImGui::DragFloat("FOV", &fov, 0.05f, 0.f, 0.f, "%.2f"))
			{
				camera->frustum.verticalFov = fov * DEGTORAD;
				camera->setAspectRatio(aspectRatio);
			}

			if (ImGui::DragFloat("Aspect Ratio", &aspectRatio, 0.05f, 0.f, 0.f, "%.2f"))
			{
				camera->setAspectRatio(aspectRatio);
			}
		}
		}

		C_ParticleSystem* particle_system = (C_ParticleSystem*)gameObject->GetComponent(Component::Type::ParticleSystem);
		if (particle_system != nullptr) {
			if (ImGui::CollapsingHeader("Particle System"))
			{


			}
		}

		if (ImGui::BeginMenu("Add Component"))
		{
			//There is no option to add Transform Component because all the gameObjects already have a Transform

			//TODO: Mesh is created with NULL values
			/*if (gameObject->GetComponent(Component::Type::Mesh) == false)
				if (ImGui::MenuItem("Mesh", nullptr))
					gameObject->CreateComponent(Component::Type::Mesh);*/				

			//TODO: Material is created with NULL values
			/*if (gameObject->GetComponent(Component::Type::Material) == false)
				if (ImGui::MenuItem("Material", nullptr)) 
					gameObject->CreateComponent(Component::Type::Material);*/

			if (gameObject->GetComponent(Component::Type::Camera) == false)
				if (ImGui::MenuItem("Camera", nullptr)) 
					gameObject->CreateComponent(Component::Type::Camera);

			if (gameObject->GetComponent(Component::Type::ParticleSystem) == false)
				if (ImGui::MenuItem("Particle System", nullptr)) 
					gameObject->CreateComponent(Component::Type::ParticleSystem);

			ImGui::EndMenu();
		}
	}	

	ImGui::End();
}

void W_Inspector::SetShowWindow()
{
	showWindow = !showWindow;
}