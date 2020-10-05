#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"

#include "Primitive.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"
#include "glew/glew.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

bool ModuleSceneIntro::Start()
{
	bool ret = true;

	float f;
	char* buf;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	// Inputs
	if ((App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RCTRL) == KEY_REPEAT) && App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) 
		showDemoWindow = !showDemoWindow;

	// Gui
	ShowMenuBar();

	if (showDemoWindow)
		ShowDemoWindow();

	if (showAboutWindow)
		ShowAboutWindow();

	if (showConfigurationWindow)
		ShowConfigurationWindow();

	return UPDATE_CONTINUE;
}

bool ModuleSceneIntro::CleanUp()
{
	bool ret = true;

	return ret;
}

void ModuleSceneIntro::ShowMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				App->CloseApp();
			}			
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit")) {
			if (ImGui::MenuItem("Configuration")) {
				showConfigurationWindow = !showConfigurationWindow;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::MenuItem("Demo Window", "CTRL+D", showDemoWindow))
				showDemoWindow = !showDemoWindow;

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About")) {
				showAboutWindow = !showAboutWindow;
			}

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void ModuleSceneIntro::ShowDemoWindow()
{
	ImGui::ShowDemoWindow();
}

void ModuleSceneIntro::ShowAboutWindow()
{
	if (!ImGui::Begin("About", &showAboutWindow))
	{
		ImGui::End();
		return;
	}

	ImGui::Text("TurboX Engine v0.1");
	ImGui::Text("The next generation 3D Game Engine");
	ImGui::Text("Authors: ");
	if (ImGui::SmallButton("Pablo Galve"))
		ShellExecuteA(NULL, "open", "https://github.com/pablogalve", NULL, NULL, SW_SHOWNORMAL);
	if (ImGui::SmallButton("Macia Dalmau"))
		ShellExecuteA(NULL, "open", "https://github.com/maciadalmau", NULL, NULL, SW_SHOWNORMAL);
	ImGui::Separator();
	
	ImGui::Text("3rd Party Libraries used:");

	//SDL Version
	ImGui::BulletText("SDL %d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);

	//OpenGL
	ImGui::BulletText("OpenGL 3");

	//ImGui Version
	ImGui::BulletText("ImGui %s", ImGui::GetVersion());
	
	//MathGeoLib
	ImGui::BulletText("MathGeoLib 1.5");

	//Glew
	ImGui::BulletText("Glew %d.%d.%d", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR, GLEW_VERSION_MICRO);

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

void ModuleSceneIntro::ShowConfigurationWindow()
{
	ImGui::Begin("Configuration", &showConfigurationWindow);

	if (ImGui::CollapsingHeader("Application"))
	{

	}	
	if (ImGui::CollapsingHeader("Audio"))
	{

	}
	if (ImGui::CollapsingHeader("Camera"))
	{

	}
	if (ImGui::CollapsingHeader("Gui"))
	{

	}
	if (ImGui::CollapsingHeader("Input"))
	{

	}
	if (ImGui::CollapsingHeader("Physics"))
	{

	}
	if (ImGui::CollapsingHeader("Renderer"))
	{

	}
	if (ImGui::CollapsingHeader("Window"))
	{

	}
	if (ImGui::CollapsingHeader("Hardware"))
	{
		//Hardware Detection

		//SDL Version
		SDL_version sdl_version;
		SDL_GetVersion(&sdl_version);
		ImGui::Text("SDL Version: %d.%d.%d", sdl_version.major, sdl_version.minor, sdl_version.patch);
		ImGui::Separator();

		//CPUs
		ImGui::Text("CPUs: ");

		//System RAM
		ImGui::Text("System RAM: ");

		//Caps
		ImGui::Text("Caps: ");
		ImGui::Separator();

		//GPU
		ImGui::Text("GPU: ");

		//Brand
		ImGui::Text("Brand: ");

		//VRAM
		ImGui::Text("VRAM Budget: ");
		ImGui::Text("VRAM Usage: ");
		ImGui::Text("VRAM Available: ");
		ImGui::Text("VRAM Reserved: ");
	}

	ImGui::End();
}
