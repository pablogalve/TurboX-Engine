#include "Component_ParticleSystem.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleResources.h"
#include "ModuleInput.h"
#include "Libraries/pcg-c-basic-0.9/pcg_basic.h"
#include "Libraries/ImGui/imgui.h"
#include "Libraries/ImGui/imgui_impl_opengl3.h"
#include "Libraries/ImGui/imgui_impl_sdl.h"
#include "ModuleTimeManagement.h"
#include "ParticleEmitter.h"

C_ParticleSystem::C_ParticleSystem(Component::Type type, GameObject* owner) :Component(type, owner)
{
	maxParticles = 200;
		
	particleReferenceGUI = new Particle();
	particleReferenceGUI->lifetime = 2.f;
	particleReferenceGUI->direction = { 0,1,0 };
	particleReferenceGUI->size = 1.f;
	particleReferenceGUI->dirVariation = 180.0f;
	particleReferenceGUI->speed = 2.f;
	particleReferenceGUI->color = Blue;

	particle_material = nullptr;
	//res_mesh = App->resources->GetBillboard();
}

C_ParticleSystem::~C_ParticleSystem()
{
}

Component::Type C_ParticleSystem::GetComponentType()
{
	return Component::Type::ParticleSystem;
}

void C_ParticleSystem::Init()
{
	for (size_t i = 0; i < emitters.size(); i++)
	{
		emitters[i].Init();
	}
}

void C_ParticleSystem::Update()
{
	//if (!App->timeManagement->IsPaused()) { //Only update the emitters if the engine is in play mode
		for (size_t i = 0; i < emitters.size(); i++)
		{
			emitters[i].UpdateModules();
		}
	//}
	for (size_t i = 0; i < emitters.size(); i++)
	{
		emitters[i].Draw();
	}
}

void C_ParticleSystem::Reset()
{
	for (size_t i = 0; i < emitters.size(); i++)
	{
		emitters[i].Reset();
	}
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

void C_ParticleSystem::UpdateParticleGUI(Particle* newParticleReference)
{
	particleReferenceGUI = newParticleReference;
}
