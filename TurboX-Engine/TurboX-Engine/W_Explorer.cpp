#include "W_Explorer.h"

W_Explorer::W_Explorer()
{
}

W_Explorer::~W_Explorer()
{
}

void W_Explorer::Draw()
{
	ImGui::Begin("Explorer");

	ImGui::Text("This is the explorer");

	ImGui::End();
}

void W_Explorer::SetShowWindow()
{
	showWindow = !showWindow;
}
