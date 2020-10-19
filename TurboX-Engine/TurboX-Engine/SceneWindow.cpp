#include "SceneWindow.h"

SceneWindow::SceneWindow()
{
}

SceneWindow::~SceneWindow()
{
}

void SceneWindow::Draw()
{
	ImGui::Begin("Scene");

	ImGui::End();
}

void SceneWindow::SetShowWindow()
{
	showWindow = !showWindow;
}
