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

	//Return if there are no objects selected
	if (gameObject == nullptr) 
	{
		ImGui::End();
		return; 
	}

	if(gameObject->mesh != nullptr)
		ImGui::Checkbox("Enabled", &gameObject->mesh->active); ImGui::SameLine();
		
	strcpy(nameBuffer, gameObject->name.c_str());

	if(ImGui::InputText(" ", nameBuffer, IM_ARRAYSIZE(nameBuffer)))		
		gameObject->name.assign(nameBuffer);

	//Draw components in the inspector
	if (gameObject->transform != nullptr) DrawTransform(gameObject->transform);
	if (gameObject->mesh != nullptr) DrawMesh(gameObject->mesh);	
	if (gameObject->material != nullptr) DrawMaterial(gameObject->material);
	if (gameObject->camera != nullptr) DrawCamera(gameObject->camera);
	if (gameObject->particle_system != nullptr)DrawParticleSystem(gameObject->particle_system);
	if (gameObject->billboard != nullptr)DrawBillboard(gameObject->billboard);

	if (ImGui::BeginMenu("Add Component"))
	{
		//There is no option to add Transform Component because all the gameObjects already have a Transform

		//TODO: Mesh is created with NULL values
		/*if (GetComponent(Component::Type::Mesh) == false)
			if (ImGui::MenuItem("Mesh", nullptr))
				CreateComponent(Component::Type::Mesh);*/				

		//TODO: Material is created with NULL values
		/*if (GetComponent(Component::Type::Material) == false)
			if (ImGui::MenuItem("Material", nullptr)) 
				CreateComponent(Component::Type::Material);*/

		if (gameObject->GetComponent(Component::Type::Camera) == false)
			if (ImGui::MenuItem("Camera", nullptr)) 
				gameObject->CreateComponent(Component::Type::Camera);

		if (gameObject->GetComponent(Component::Type::ParticleSystem) == false)
		{
			if (ImGui::MenuItem("Particle System", nullptr))
			{
				gameObject->CreateComponent(Component::Type::ParticleSystem);
				//TODO: Create emitters elsewhere
				gameObject->particle_system->emitters.push_back(EmitterInstance());
				ParticleEmitter* emitterReference = new ParticleEmitter();
				gameObject->particle_system->emitters.back().Init(emitterReference);
				gameObject->particle_system->emitters.back().owner = (C_ParticleSystem*)gameObject->GetComponent(Component::Type::ParticleSystem);	//Set EmitterInstance's owner
				delete emitterReference;
			}
		}

		if (gameObject->GetComponent(Component::Type::Billboard) == false)
			if (ImGui::MenuItem("Billboard", nullptr))				
				gameObject->CreateComponent(Component::Type::Billboard);

		ImGui::EndMenu();
	}

	ImGui::End();
}

void W_Inspector::SetShowWindow()
{
	showWindow = !showWindow;
}

void W_Inspector::DrawTransform(C_Transform* transform)
{
	if (ImGui::CollapsingHeader("Transform"), ImGuiTreeNodeFlags_DefaultOpen)
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

void W_Inspector::DrawMesh(C_Mesh* mesh)
{
	if (ImGui::CollapsingHeader("Mesh"))
	{
		ImVec4 yellow(1.0f, 0.8f, 0.0f, 1.0f);

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
		//ImGui::Checkbox("Face Normals:", &mesh->face_normals_active); //TODO
	}
}

void W_Inspector::DrawMaterial(C_Material* material)
{
	if (ImGui::CollapsingHeader("Material"))
	{
		ImVec4 yellow(1.0f, 0.8f, 0.0f, 1.0f);

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

void W_Inspector::DrawCamera(C_Camera* camera)
{
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

void W_Inspector::DrawParticleSystem(C_ParticleSystem* particle_system)
{
	if (ImGui::CollapsingHeader("Particle System"))
	{
		ImGui::Text("Particle Emitter");
		ImGui::Text("Set to 0 for an infinite lifetime.");
		ImGui::SliderFloat("Lifetime", &particle_system->lifetime, 0.0f, 120.0f, "%.1f");

		if (ImGui::Button("Reset")) particle_system->lifetime = 0;

		ImGui::Text("Maximum Particles");
		ImGui::Text("Set to 0 for unlimited particles.");
		//ImGui::SliderInt("MaxParticles", &particle_system->lifetime, 0.0f, 200.0f, "%.1f");
	}
}

void W_Inspector::DrawBillboard(C_Billboard* billboard)
{
	if (ImGui::CollapsingHeader("Billboard")) {

		//Billboard Alignment
		ImGui::Text("Current Billboard: %s", billboard->GetAlignmentText().c_str());

		//Change Billboard
		if (ImGui::BeginMenu("Change billboard")) {
			if (ImGui::MenuItem("Screen")) billboard->SetAlignment(Billboarding_Alignment::SCREEN_ALIGNED);
			if (ImGui::MenuItem("World")) billboard->SetAlignment(Billboarding_Alignment::WORLD_ALIGNED);
			if (ImGui::MenuItem("Axis")) billboard->SetAlignment(Billboarding_Alignment::AXIS_ALIGNED);

			ImGui::EndMenu();
		}

		//Material
		if (billboard->owner->material == nullptr)
		{
			if (ImGui::Button("Add Material"))
				ImGui::OpenPopup("add_material");

			if (ImGui::BeginPopup("add_material"))
			{
				//TODO: Add Material
				ImGui::EndPopup();
			}
		}
		else {
			//TODO: Show material info
		}
	}
}
