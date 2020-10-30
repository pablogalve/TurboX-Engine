#include "Hierarchy.h"
#include "ModuleScene.h"
#include "Application.h"

Hierarchy::Hierarchy()
{
	open_pop_up = false;
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

	if (open_pop_up)
		OpenPopUpWindow();

	ImGuiTreeNodeFlags default_flags = ImGuiTreeNodeFlags_NoTreePushOnOpen;
	DrawGameObject(App->scene->GetRoot(), default_flags, App->scene->GetRoot());

	ImGui::End();
}

void Hierarchy::DrawGameObject(GameObject* gameObject, ImGuiTreeNodeFlags default_flags, GameObject* root)
{	
	bool drawAgain = true;

	ImGuiTreeNodeFlags flags = default_flags;	
	
	if (gameObject->childs.empty()) {
		flags |= ImGuiTreeNodeFlags_Leaf;
	}

	if (gameObject->Get_IsSelected())
		flags |= ImGuiTreeNodeFlags_Selected;

	if (gameObject != root)
		drawAgain = ImGui::TreeNodeEx(gameObject, flags, gameObject->name.c_str());
	else
		drawAgain = true;

	if (ImGui::IsItemClicked(0))
	{
		if (gameObject->Get_IsSelected() == true) {
			UnSelectSingle(gameObject);
		}
		else {
			DeselectAll();
			SelectSingle(gameObject);
		}
	}
	else if (ImGui::IsItemClicked(1) && ImGui::IsWindowHovered()) {
		open_pop_up = true;
		if (gameObject->Get_IsSelected() == false) {
			DeselectAll();
			SelectSingle(gameObject);
		}
	}	

	if (drawAgain)
	{
		for (uint i = 0; i < gameObject->childs.size(); i++)
		{
			DrawGameObject(gameObject->childs[i], flags, root);
		}		
	}		
}

void Hierarchy::OpenPopUpWindow()
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
				//App->scene->DestroyGameObject(selectedGameObjects[0]);
			}
			open_pop_up = false;
		}

		ImGui::EndPopup();
	}
}

void Hierarchy::SetShowWindow()
{
	showWindow = !showWindow;
}

void Hierarchy::SelectSingle(GameObject* gameObject)
{
	gameObject->Select();
	selectedGameObjects.push_back(gameObject);
}

void Hierarchy::UnSelectSingle(GameObject* gameObject)
{
	gameObject->Unselect();

	vector<GameObject*>::iterator it = selectedGameObjects.begin();
	while (it != selectedGameObjects.end()) 
	{
		if ((*it) == gameObject)
		{
			selectedGameObjects.erase(it);
			break;
		}
	}
}

void Hierarchy::DeselectAll()
{
	for (size_t i = 0; i < selectedGameObjects.size(); i++)
	{
		selectedGameObjects[i]->Unselect();
	}
	selectedGameObjects.clear();
}
