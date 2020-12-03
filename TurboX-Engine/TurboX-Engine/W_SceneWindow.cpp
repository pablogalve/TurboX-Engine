#include "W_SceneWindow.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleCamera3D.h"
#include "Component.h"
#include "Component_Camera.h"
#include "ModuleEditor.h"
#include "ModuleRenderer3D.h"
#include "MathGeoLib/MathGeoLib.h"

W_SceneWindow::W_SceneWindow()
{
	size = { 0,0 };
}

W_SceneWindow::~W_SceneWindow()
{
	
}

void W_SceneWindow::Draw(GLuint texture)
{
	ImGui::Begin("Scene");


	float2 newSize = float2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);

	if(newSize.x != size.x || newSize.y != size.y)
	{
		size = newSize;
		float newAR = size.x / size.y;
		App->camera->camera->setAspectRatio(newAR);
		App->renderer3D->changedFOV = true;
	}
	
	ImGui::SetCursorPos({ 0,0 });
	App->editor->sceneX = ImGui::GetCursorPosX() + ImGui::GetWindowPos().x;
	App->editor->sceneY = ImGui::GetCursorPosY() + ImGui::GetWindowPos().y;
	App->editor->sceneW = size.x;
	App->editor->sceneH = size.y;

	ImGui::Image((ImTextureID)App->renderer3D->texColorBuffer, { (float)size.x, (float)size.y }, { 0,1 }, { 1,0 });

	ImGuizmo::SetDrawlist();

	if (App->scene->selected_GO)
		App->scene->DrawGuizmo(App->scene->guizmoOperation);


	ImGui::End();
}

void W_SceneWindow::SetShowWindow()
{
	showWindow = !showWindow;
}
