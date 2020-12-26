#include "W_About.h"
#include "SDL/include/SDL.h"
#include "glew/glew.h"
#include "Application.h"

W_About::W_About()
{
	showWindow = false;
}

W_About::~W_About()
{
}

void W_About::Draw() 
{
	ImVec4 yellow(1.0f, 0.8f, 0.0f, 1.0f); //We'll use yellow to print the results

	if (!ImGui::Begin("About", &showWindow))
	{
		ImGui::End();
		return;
	}

	ImGui::Text("%s v%.2lf", App->GetEngineName(), App->GetEngineVersion());
	ImGui::Text("The next generation 3D Game Engine");
	ImGui::Text("Authors: ");
	if (ImGui::SmallButton("Pablo Galve"))
		ShellExecuteA(NULL, "open", "https://github.com/pablogalve", NULL, NULL, SW_SHOWNORMAL);
	if (ImGui::SmallButton("Macia Dalmau"))
		ShellExecuteA(NULL, "open", "https://github.com/maciadalmau", NULL, NULL, SW_SHOWNORMAL);
	ImGui::Separator();
	
	ImGui::Text("3rd Party Libraries used:");

	//SDL Version
	SDL_version sdl_version;
	SDL_GetVersion(&sdl_version);
	ImGui::BulletText("SDL Version:");
	ImGui::SameLine();
	ImGui::TextColored(yellow, "%d.%d.%d", sdl_version.major, sdl_version.minor, sdl_version.patch); ImGui::SameLine();
	if (ImGui::SmallButton("Open SDL Website"))
		ShellExecuteA(NULL, "open", "https://libsdl.org/", NULL, NULL, SW_SHOWNORMAL);

	//OpenGL
	int major = 0;
	int minor = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	ImGui::BulletText("OpenGL ", major, minor); ImGui::SameLine();
	ImGui::TextColored(yellow, "%d.%d.%d", sdl_version.major, sdl_version.minor, sdl_version.patch); ImGui::SameLine();
	if (ImGui::SmallButton("Open OpenGL Website"))
		ShellExecuteA(NULL, "open", "https://www.opengl.org/", NULL, NULL, SW_SHOWNORMAL);

	//ImGui Version
	ImGui::BulletText("ImGui "); ImGui::SameLine();
	ImGui::TextColored(yellow, "%s", ImGui::GetVersion()); ImGui::SameLine();
	if (ImGui::SmallButton("Open ImGui Website"))
		ShellExecuteA(NULL, "open", "https://github.com/ocornut/imgui", NULL, NULL, SW_SHOWNORMAL);

	////MathGeoLib
	ImGui::BulletText("MathGeoLib "); ImGui::SameLine();
	ImGui::TextColored(yellow, "1.5"); ImGui::SameLine();
	if (ImGui::SmallButton("Open MathGeoLib Website"))
		ShellExecuteA(NULL, "open", "https://github.com/juj/MathGeoLib", NULL, NULL, SW_SHOWNORMAL);

	//Glew
	ImGui::BulletText("Glew "); ImGui::SameLine();
	ImGui::TextColored(yellow, "%d.%d.%d", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR, GLEW_VERSION_MICRO); ImGui::SameLine();
	if (ImGui::SmallButton("Open Glew Website"))
		ShellExecuteA(NULL, "open", "https://github.com/nigels-com/glew", NULL, NULL, SW_SHOWNORMAL);

	//DevIL
	ImGui::BulletText("DevIL "); ImGui::SameLine();
	ImGui::TextColored(yellow, "1.8.0"); ImGui::SameLine();
	if (ImGui::SmallButton("Open DevIL Website"))
		ShellExecuteA(NULL, "open", "http://openil.sourceforge.net/", NULL, NULL, SW_SHOWNORMAL);

	//Assimp
	ImGui::BulletText("Assimp "); ImGui::SameLine();
	ImGui::TextColored(yellow, "3.1.1"); ImGui::SameLine();
	if (ImGui::SmallButton("Open Assimp Website"))
		ShellExecuteA(NULL, "open", "http://openil.sourceforge.net/", NULL, NULL, SW_SHOWNORMAL);

	ImGui::Separator();

	ImGui::Text("License:");
	ImGui::Spacing();
	ImGui::Text("MIT License:");
	ImGui::Spacing();
	ImGui::TextWrapped("Copyright (c) 2020 TurboX Engine");
	ImGui::Spacing();
	ImGui::TextWrapped(
		"Permission is hereby granted, free of charge, to any person obtaining a copy"
		"of this software and associated documentation files Genesis Engine, to deal"
		"in the Software without restriction, including without limitation the rights"
		"to use, copy, modify, merge, publish, distribute, sublicense, and /or sell"
		"copies of the Software, and to permit persons to whom the Software is"
		"furnished to do so, subject to the following conditions : ");
	ImGui::Spacing();

	ImGui::TextWrapped(
		"The above copyright notice and this permission notice shall be included in all"
		"copies or substantial portions of the Software.");
	ImGui::Spacing();

	ImGui::TextWrapped(
		"THE SOFTWARE IS PROVIDED 'AS I', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR"
		"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,"
		"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE"
		"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER"
		"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,"
		"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE"
		"SOFTWARE.");

	ImGui::End();
}

void W_About::SetShowWindow()
{
	showWindow = !showWindow;
}
