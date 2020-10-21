#include "Explorer.h"

Explorer::Explorer()
{
}

Explorer::~Explorer()
{
}

void Explorer::Draw()
{
	ImGui::Begin("Explorer");

	ImGui::Text("This is the explorer");

	ImGui::End();
}

void Explorer::SetShowWindow()
{
	showWindow = !showWindow;
}
