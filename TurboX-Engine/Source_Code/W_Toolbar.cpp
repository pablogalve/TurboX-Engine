#include "W_Toolbar.h"
#include "Libraries/glew/glew.h"
#include "Libraries/glew/wglew.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleTimeManagement.h"
#include "ModuleScene.h"

W_Toolbar::W_Toolbar()
{
}

W_Toolbar::~W_Toolbar()
{
}

void W_Toolbar::Draw()
{
	ImGui::Begin("Toolbar");

	ImGui::Text("Display: "); ImGui::SameLine();

	if (ImGui::Checkbox("Cull Face", &App->renderer3D->_cull_face))
		App->renderer3D->GL_Enable(GL_CULL_FACE, App->renderer3D->_cull_face);
	ImGui::SameLine();
	if (ImGui::Checkbox("Lighting", &App->renderer3D->_lighting))
		App->renderer3D->GL_Enable(GL_LIGHTING, App->renderer3D->_lighting);
	ImGui::SameLine();
	if (ImGui::Checkbox("Wireframe", &App->renderer3D->_wireframe))
		App->renderer3D->SetWireframeMode(App->renderer3D->_wireframe);
	ImGui::SameLine();
	if (ImGui::Checkbox("Texture", &App->renderer3D->_texture))
		App->renderer3D->GL_Enable(GL_TEXTURE_2D, App->renderer3D->_texture);
	ImGui::SameLine();
	if (ImGui::Checkbox("Depth test", &App->renderer3D->_depth_test))
		App->renderer3D->GL_Enable(GL_DEPTH_TEST, App->renderer3D->_depth_test);
	ImGui::SameLine();
	if (ImGui::Checkbox("Color material", &App->renderer3D->_color_material))
		App->renderer3D->GL_Enable(GL_COLOR_MATERIAL, App->renderer3D->_color_material);
	ImGui::SameLine();
	if (ImGui::Checkbox("Bounding Boxes", &App->renderer3D->ShowBB));
	ImGui::SameLine();
	if (ImGui::Checkbox("Show Ray Cast", &App->renderer3D->ShowRayCast));

	if (ImGui::ArrowButton("Play", ImGuiDir_Right))
	{
		MY_LOG("Play button pressed");
		if (App->timeManagement->IsStopped()) {
			App->timeManagement->Play();
			//TODO: Call the Init of the particles
			App->scene->PlayScene(App->scene->GetRoot(), App->scene->GetRoot());
		}
		else if (App->timeManagement->IsPaused()) {
			App->timeManagement->Resume();
		}
		App->scene->inGame = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("||", { 23, 19 }))
	{
		MY_LOG("Pause button pressed");
		if (App->scene->inGame && !App->timeManagement->IsPaused()) {
			App->timeManagement->Pause();
		}

	}
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f,0,0,1 });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1,0.2f,0,1 });
	if (ImGui::Button("STOP", { 40, 19 }))
	{
		MY_LOG("Stop button pressed");
		if (App->scene->inGame) {
			App->timeManagement->Stop();
			App->scene->inGame = false;
			App->scene->StopScene(App->scene->GetRoot(), App->scene->GetRoot());
		}
	}
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	ImGui::SliderFloat("Speed up/down", App->timeManagement->GetTimeScale(), 0.1f, 2.0f, "%.1f");
	ImGui::Text("Real Time: %.1f", App->timeManagement->GetRealTimeInSeconds());
	ImGui::Text("Game Time: %.1f", App->timeManagement->GetGameTimeInSeconds());

	ImGui::Text("");
	ImGui::Text("Delta Time: %.3f", App->timeManagement->GetGameDeltaTime());

	ImGui::End();
}

void W_Toolbar::SetShowWindow()
{
	showWindow = !showWindow;
}
