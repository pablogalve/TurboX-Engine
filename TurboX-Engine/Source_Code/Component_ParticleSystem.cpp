#include "Component_ParticleSystem.h"
#include "Application.h"
#include "Component_Material.h"
#include "ModuleScene.h"
#include "pcg-c-basic-0.9/pcg_basic.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"

C_ParticleSystem::C_ParticleSystem(Component::Type type, GameObject* owner) :Component(type, owner)
{
	maxParticles = 200;
	resourceParticleSystem = nullptr;
	lifetime = { 2,5 };
	direction = { 0,1,0 };
	size = { 15,30 };
	dirVariation = 180.0f;
	speed = { 2, 3 };
}

C_ParticleSystem::~C_ParticleSystem()
{
}

Component::Type C_ParticleSystem::GetComponentType()
{
	return Component::Type::ParticleSystem;
}

void C_ParticleSystem::Update()
{
	for (size_t i = 0; i < emitters.size(); i++)
	{
		emitters[i].UpdateModules();
	}
}

void C_ParticleSystem::Reset()
{
	
}

void C_ParticleSystem::Save()
{
}

void C_ParticleSystem::Load()
{
}

float C_ParticleSystem::GetRandomFloat(range<float> number)
{
	return (ldexp(pcg32_random(), -32) * (number.max - number.min)) + number.min;
}

uint C_ParticleSystem::GetRandomUint(range<uint> number)
{
	return (ldexp(pcg32_random(), -32) * (number.max - number.min)) + number.min;
}

Color C_ParticleSystem::GetRandomColor(range<Color> r)
{
	Color c;
	c.r = (ldexp(pcg32_random(), -32) * (r.max.r - r.min.r)) + r.min.r;
	c.g = (ldexp(pcg32_random(), -32) * (r.max.g - r.min.g)) + r.min.g;
	c.b = (ldexp(pcg32_random(), -32) * (r.max.b - r.min.b)) + r.min.b;
	c.a = (ldexp(pcg32_random(), -32) * (r.max.a - r.min.a)) + r.min.a;

	return c;
}

void C_ParticleSystem::AddMaterial()
{
	for (std::list<C_Material*>::iterator item = App->scene->materials.begin(); item != App->scene->materials.end(); item++) {

		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;

		node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		
		ImGui::TreeNodeEx((*item)->GetName().c_str(), node_flags);

		if (ImGui::IsItemClicked())
		{
			//material = (*item);

		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			//ImGui::ColorButton("Color##3c", *(ImVec4*)&(*item)->color, 0, ImVec2(80, 80));
			ImGui::EndTooltip();
		}
	}
}
