#include "W_Resources.h"
#include "Application.h"
#include "Resource.h"
#include "ModuleResources.h"

W_Resources::W_Resources()
{
}

W_Resources::~W_Resources()
{
}

void W_Resources::Draw()
{
	ImGui::Begin("Resources");

	DrawResourcesChilds(App->resources->GetResourcesList());

	ImGui::End();
}

void W_Resources::SetShowWindow()
{
	showWindow = !showWindow;
}

void W_Resources::DrawResourcesChilds(std::map<uint, Resource*> resources)
{
	uint flags = 0;
	flags |= ImGuiTreeNodeFlags_Leaf;
	for (std::map<uint, Resource*>::iterator goIterator = resources.begin(); goIterator != resources.end(); goIterator++)
	{
		Resource* res = (*goIterator).second;

		std::string name = res->GetName();
		if (ImGui::TreeNodeEx(name.c_str(), flags)) {
			if (ImGui::IsItemHovered()) {
				ImGui::BeginTooltip();
				ImGui::Text("UUID: %d", res->GetUUID());
				ImGui::Text("Directory: %s", res->GetPath());
				ImGui::Text("Reference Count: %d", res->GetCountReferences());
				ImGui::EndTooltip();
			}
			ImGui::TreePop();
		}
		res = nullptr;
	}
}
