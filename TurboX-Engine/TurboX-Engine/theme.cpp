#include "theme.h"

Theme::Theme()
{
	showWindow = false;
	current_theme = Themes::DARK;
}

Theme::~Theme()
{	
}

void Theme::Draw()
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

void Theme::SetShowWindow()
{
	showWindow = !showWindow;
}