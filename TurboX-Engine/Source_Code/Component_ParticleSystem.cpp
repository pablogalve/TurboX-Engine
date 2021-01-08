#include "Component_ParticleSystem.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleResources.h"
#include "ModuleInput.h"
#include "Libraries/pcg-c-basic-0.9/pcg_basic.h"
#include "Libraries/ImGui/imgui.h"
#include "Libraries/ImGui/imgui_impl_opengl3.h"
#include "Libraries/ImGui/imgui_impl_sdl.h"

C_ParticleSystem::C_ParticleSystem(Component::Type type, GameObject* owner) :Component(type, owner)
{
	maxParticles = 200;
	lifetime = { 2,5 };
	direction = { 0,1,0 };
	size = { 1,30 };
	dirVariation = 180.0f;
	speed = { 2, 3 };
	particle_material = nullptr;
	color = { Blue, Green};
	//res_mesh = App->resources->GetBillboard();
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

void C_ParticleSystem::AddMaterial(std::map<uint, Resource*> resources)
{
	uint flags = 0;
	flags |= ImGuiTreeNodeFlags_Leaf;

	for (std::map<uint, Resource*>::iterator goIterator = resources.begin(); goIterator != resources.end(); goIterator++)
	{
		Resource* res = (*goIterator).second;

		std::string name = res->GetName();
		
		if (App->input->GetFileType(res->GetPath()) == FileType::PNG)
		{
			if (ImGui::TreeNodeEx(name.c_str(), flags)) {
				
				ImGui::TreePop();

				if (ImGui::IsItemClicked())
				{
					particle_material = new C_Material(Component::Type::Material, this->owner);

					particle_material->SetResource(res->GetUUID());

				}
			}
		}		
		res = nullptr;
	}
}
