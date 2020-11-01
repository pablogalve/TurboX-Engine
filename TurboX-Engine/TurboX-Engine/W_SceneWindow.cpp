#include "W_SceneWindow.h"

W_SceneWindow::W_SceneWindow()
{
}

W_SceneWindow::~W_SceneWindow()
{
	
}

void W_SceneWindow::Draw(GLuint texture)
{
	ImGui::Begin("Scene");

	ImVec2 windowSize = ImGui::GetWindowSize();
	ImGui::Image((ImTextureID)texture, windowSize, ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
}

void W_SceneWindow::SetShowWindow()
{
	showWindow = !showWindow;
}
