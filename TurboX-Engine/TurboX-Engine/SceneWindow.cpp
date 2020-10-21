#include "SceneWindow.h"

SceneWindow::SceneWindow()
{
}

SceneWindow::~SceneWindow()
{
	
}

void SceneWindow::Draw(GLuint texture)
{
	ImGui::Begin("Scene");

	ImVec2 windowSize = ImGui::GetWindowSize();
	ImGui::Image((ImTextureID)texture, windowSize, ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
}

void SceneWindow::SetShowWindow()
{
	showWindow = !showWindow;
}
