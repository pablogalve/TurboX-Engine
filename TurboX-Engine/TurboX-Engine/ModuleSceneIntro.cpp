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
{
	showDemoWindow = false;
	showAboutWindow = false;
	showConfigurationWindow = true;

	fps_log.resize(100);
	ms_log.resize(100);
}

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
			if (ImGui::MenuItem("Documentation")) {
				ShellExecuteA(NULL, "open", "https://github.com/pablogalve/TurboX-Engine", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Download lastest")) {
				ShellExecuteA(NULL, "open", "https://github.com/pablogalve/TurboX-Engine/releases", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Report a bug")) {
				ShellExecuteA(NULL, "open", "https://github.com/pablogalve/TurboX-Engine/issues", NULL, NULL, SW_SHOWNORMAL);
			}
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

	ImGui::Text("Options");

	if (ImGui::CollapsingHeader("Application"))
	{
		//FPS
		fps_log.erase(fps_log.begin());
		fps_log.push_back(ImGui::GetIO().Framerate);
		char title[25];
		sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
		ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		
		//Milliseconds
		ms_log.erase(ms_log.begin());
		ms_log.push_back(1 / (ImGui::GetIO().Framerate / 1000));
		sprintf_s(title, 25, "Milliseconds %.1f", ms_log[ms_log.size() - 1]);
		ImGui::PlotHistogram("##framerate", &ms_log[0], ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));
	}	
	if (ImGui::CollapsingHeader("File System"))
	{

	}
	if (ImGui::CollapsingHeader("Input"))
	{

	}
	if (ImGui::CollapsingHeader("Window"))
	{
		float bright = App->window->GetBrightness();
		ImGui::SliderFloat("Brightness", &bright, 0, 1.0f);
		App->window->SetBrightness(bright);

		int w, h;
		App->window->GetSize(w, h);
		
		int minWidthVal = 640;
		int maxWidthVal = 1920;
		if (ImGui::SliderInt("Width", &w, minWidthVal, maxWidthVal)) 
		{
			App->window->SetSize(w, h);
		}

		int minHeightVal = 480;
		int maxHeightVal = 1080;
		if (ImGui::SliderInt("Height", &h, minHeightVal, maxHeightVal)) {
			App->window->SetSize(w, h);
		}

		bool fullscreen = App->window->IsFullscreen();
		
		if (ImGui::Checkbox("Fullscreen", &fullscreen)) 
		{
			fullscreen != fullscreen;
			App->window->SetFullscreen(fullscreen);
		}

		ImGui::SameLine();

		bool resizable = App->window->IsResizable();

		if (ImGui::Checkbox("Resizable ", &resizable))
		{
			resizable != resizable;
			App->window->SetResizable(resizable);
		}

		bool borderless = App->window->IsBorderless();

		if (ImGui::Checkbox("Borderless", &borderless)) 
		{
			borderless != borderless;
			App->window->SetBorderless(borderless);
		}

		ImGui::SameLine();

		bool fullDesktop = App->window->IsFullscreenDesktop();
		if (ImGui::Checkbox("Full Desktop", &fullDesktop)) {
			fullDesktop != fullDesktop;
			App->window->SetFullscreenDesktop(fullDesktop);
		}
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
