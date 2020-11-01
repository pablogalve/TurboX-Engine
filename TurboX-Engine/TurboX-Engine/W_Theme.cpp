#include "W_Theme.h"

W_Theme::W_Theme()
{
	showWindow = false;
	current_theme = Themes::DARK;
}

W_Theme::~W_Theme()
{	
}

void W_Theme::Draw()
{
	ImGui::Begin("Editor Theme");

	ImGui::SetWindowFontScale(1.3);
	ImGui::Text("Editor Theme");
	ImGui::SetWindowFontScale(1.0);

	// DARK THEME
	if (ImGui::MenuItem("Dark")) {
		ImGui::StyleColorsDark();
		current_theme = Themes::DARK;		
	}
	if (current_theme == Themes::DARK) {
		ImGui::SameLine();
		ImGui::TextColored({ 1,1,0,1 }, "Current Theme");
	}
	
	// LIGHT THEME
	if (ImGui::MenuItem("Light")) {
		ImGui::StyleColorsLight();
		current_theme = Themes::LIGHT;
	}
	if (current_theme == Themes::LIGHT) {
		ImGui::SameLine();
		ImGui::TextColored({ 0,0,0,1 }, "Current Theme");
	}

	// CLASSIC THEME
	if (ImGui::MenuItem("Classic")) {
		ImGui::StyleColorsClassic();
		current_theme = Themes::CLASSIC;
	}
	if (current_theme == Themes::CLASSIC) {
		ImGui::SameLine();
		ImGui::TextColored({ 1,1,0,1 }, "Current Theme");
	}

	ImGui::End();
}

void W_Theme::SetShowWindow()
{
	showWindow = !showWindow;
}