#include "W_Hierarchy.h"

W_Hierarchy::W_Hierarchy()
{
}

W_Hierarchy::~W_Hierarchy()
{
}

void W_Hierarchy::Draw()
{
	ImGui::Begin("Hierarchy");

	ImGuiTreeNodeFlags default_flags = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
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

	if (gameObject->is_selected)
	{
		flags |= ImGuiTreeNodeFlags_Selected;
	}

	if (gameObject != root){
		drawAgain = ImGui::TreeNodeEx(gameObject, flags, gameObject->name.c_str());
	}
	else
		drawAgain = true;

	if (ImGui::IsItemClicked(0))
	{
		App->scene->selectGameObject(gameObject);
	}

	if (ImGui::BeginPopupContextItem((gameObject->name + "rightClick").c_str(), 1))
	{
		if (ImGui::Button("Delete"))
		{
			gameObject->to_delete = true;
		}
		ImGui::EndPopup();
	}

	if (App->scene->selected_GO != nullptr)
	{
		if (App->scene->selected_GO->to_delete == true)
		{
			App->scene->DestroyGameObject(gameObject);
		}
	}

	if (ImGui::BeginDragDropSource())
	{
		uint gameObject_UUID = gameObject->GetUUID();
		ImGui::SetDragDropPayload("Reparenting", &gameObject_UUID, sizeof(uint));
		ImGui::Text(gameObject->name.c_str());
		ImGui::EndDragDropSource();
	}
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Reparenting", ImGuiDragDropFlags_SourceAllowNullID))
		{
			GameObject* draggedGameobject = App->scene->GetGameObjectByUUID(*(uint*)payload->Data);
			if (draggedGameobject != nullptr)
				draggedGameobject->SetParent(gameObject);
		}
		ImGui::EndDragDropTarget();
	}

	if (drawAgain)
	{		
		for (uint i = 0; i < gameObject->childs.size(); i++)
		{
			if(gameObject != root) ImGui::Indent();
			DrawGameObject(gameObject->childs[i], flags, root);
			if (gameObject != root) ImGui::Unindent();
		}	
	}
}

void W_Hierarchy::SetShowWindow()
{
	showWindow = !showWindow;
}