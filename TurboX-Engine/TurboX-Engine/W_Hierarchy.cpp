#include "W_Hierarchy.h"
#include "ModuleScene.h"
#include "Application.h"

W_Hierarchy::W_Hierarchy()
{
	open_pop_up = false;
}

W_Hierarchy::~W_Hierarchy()
{
}

void W_Hierarchy::Draw()
{
	ImGui::Begin("Hierarchy");

	if (open_pop_up)
		OpenPopUpWindow();

	ImGuiTreeNodeFlags default_flags = ImGuiTreeNodeFlags_NoTreePushOnOpen;
	DrawGameObject(App->scene->GetRoot(), default_flags, App->scene->GetRoot());

	ImGui::End();
}

void W_Hierarchy::DrawGameObject(GameObject* gameObject, ImGuiTreeNodeFlags default_flags, GameObject* root)
{	
	bool drawAgain = true;
		
	ImGuiTreeNodeFlags flags = default_flags;	
	
	if (gameObject->childs.empty()) {
		flags |= ImGuiTreeNodeFlags_Leaf;
	}

	if (gameObject != root)
		drawAgain = ImGui::TreeNodeEx(gameObject, flags, gameObject->name.c_str());
	else
		drawAgain = true;

	if (ImGui::IsItemClicked(0))
	{
		App->scene->selectGameObject(gameObject);
	}

	if (drawAgain)
	{
		for (uint i = 0; i < gameObject->childs.size(); i++)
		{
			DrawGameObject(gameObject->childs[i], flags, root);
		}
	}
}

void W_Hierarchy::OpenPopUpWindow()
{
	if (ImGui::IsMouseReleased(0) || ImGui::IsMouseReleased(2))
		open_pop_up = false;
	else if (ImGui::IsMouseClicked(1))
		open_pop_up = false;

	ImGui::OpenPopup("Hierarchy Tools");

	if (ImGui::BeginPopup("Hierarchy Tools"))
	{
		if (ImGui::MenuItem("Delete"))
		{
			if (selectedGameObjects.empty() == false) {
				selectedGameObjects[0]->DeleteGameObject();
				App->scene->DestroyGameObject(selectedGameObjects[0]);
			}
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void W_Hierarchy::SetShowWindow()
{
	showWindow = !showWindow;
}