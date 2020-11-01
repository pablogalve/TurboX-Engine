#include "W_Toolbar.h"
#include "glew/glew.h"
#include "glew/wglew.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

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

	ImGui::End();
}

void W_Toolbar::SetShowWindow()
{
	showWindow = !showWindow;
}
