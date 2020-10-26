#include "Hierarchy.h"
#include "ModuleScene.h"
#include "Application.h"

Hierarchy::Hierarchy()
{
}

Hierarchy::~Hierarchy()
{
}

void Hierarchy::Draw()
{
	ImGui::Begin("Hierarchy");

	//ImGui::TreeNodeEx();

	ImGui::End();
}

void Hierarchy::Draw(Application* App)
{
	ImGui::Begin("Hierarchy");	

	ImGuiTreeNodeFlags default_flags = ImGuiTreeNodeFlags_NoTreePushOnOpen;
	DrawGameObject(App->scene->GetRoot(), default_flags, App->scene->GetRoot());

	ImGui::End();
}

void Hierarchy::DrawGameObject(GameObject* gameObject, ImGuiTreeNodeFlags default_flags, GameObject* root)
{	
	bool drawAgain = true;

	if (gameObject != root)
		drawAgain = ImGui::TreeNodeEx(gameObject, default_flags, gameObject->name.c_str());
	else
		drawAgain = true;

	ImGuiTreeNodeFlags flags = default_flags;

	if (gameObject->childs.empty()) {
		flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
	}

	if (drawAgain)
	{
		for (uint i = 0; i < gameObject->childs.size(); i++)
		{
			DrawGameObject(gameObject->childs[i], flags, root);
		}
	}	
}

void Hierarchy::SetShowWindow()
{
	showWindow = !showWindow;
}
