#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include <string>

#include "Libraries/ImGui/imgui.h"
#include "Libraries/ImGui/imgui_impl_opengl3.h"
#include "Libraries/ImGui/imgui_impl_sdl.h"
#include "Libraries/glew/glew.h"
#include "Libraries/glew/wglew.h"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Editor";

	about_window = new W_About();
	hierarchy_window = new W_Hierarchy();
	explorer_window = new W_Explorer();
	scene_window = new W_SceneWindow();
	resources_window = new W_Resources();
	inspector_window = new W_Inspector();	
	theme_window = new W_Theme();
	config_window = new W_Configuration();
	toolbar_window = new W_Toolbar();
}

ModuleEditor::~ModuleEditor()
{}

bool ModuleEditor::Start()
{
	bool ret = true;

	float f;
	char* buf;	

	return ret;
}

update_status ModuleEditor::Update(float dt)
{
	CreateDockSpace();

	// Gui
	ShowMenuBar();	

	// Display editor windows/panels
	if (showDemoWindow) ImGui::ShowDemoWindow();
	if (about_window->GetShowWindow()) about_window->Draw();
	if (showConsoleWindow)App->console->Draw("Console", &showConsoleWindow);	
	if (hierarchy_window->GetShowWindow())hierarchy_window->Draw();
	if (scene_window->GetShowWindow())scene_window->Draw(App->renderer3D->texColorBuffer);
	if (toolbar_window->GetShowWindow())toolbar_window->Draw();
	if (inspector_window->GetShowWindow())inspector_window->Draw();
	if (explorer_window->GetShowWindow()) explorer_window->Draw();
	if (resources_window->GetShowWindow())resources_window->Draw();
	if (config_window->GetShowWindow())config_window->Draw();
	if (theme_window->GetShowWindow())theme_window->Draw();

	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
	bool ret = true;

	MY_LOG("Cleaning up the Editor");

	// Delete configuration windows/panels
	delete about_window;
	delete hierarchy_window;
	delete explorer_window;
	delete inspector_window;
	delete resources_window;
	delete scene_window;
	delete theme_window;

	return ret;
}

bool ModuleEditor::LoadSettings(Config* data)
{
	showDemoWindow = data->GetBool("show_Demo_Window", false);
	showConsoleWindow = data->GetBool("show_Console_Window", false);
	return true;
}

bool ModuleEditor::SaveSettings(Config* data) const
{
	data->AddBool("show_Demo_Window", showDemoWindow);
	data->AddBool("show_Console_Window", showConsoleWindow);

	return true;
}

void ModuleEditor::CreateDockSpace()
{
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;

	// Set viewport and windows settings
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->GetWorkPos());
	ImGui::SetNextWindowSize(viewport->GetWorkSize());
	ImGui::SetNextWindowViewport(viewport->ID);

	// Set window flags
	window_flags |= ImGuiWindowFlags_NoTitleBar;

	// Disable padding
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("DockSpace", (bool*)true, window_flags);

	ImGui::PopStyleVar();

	// Create DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	ImGui::End();
}

void ModuleEditor::ShowMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save Settings"))
			{
				App->SaveEngine();
			}
			if (ImGui::MenuItem("Load Settings"))
			{
				App->LoadEngine();
			}
			if (ImGui::MenuItem("Exit", "ESC"))
			{
				App->CloseApp();
			}			
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::BeginMenu("Styling"))
			{
				if (ImGui::MenuItem("Theme", nullptr, theme_window->GetShowWindow())) theme_window->SetShowWindow();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Assets")) 
		{
			if (ImGui::MenuItem("Create Camera"))
			{
				App->scene->AddCamera();
			}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window")) {
			if (ImGui::BeginMenu("Display"))
			{
				if (ImGui::MenuItem("Hierarchy", nullptr, hierarchy_window->GetShowWindow())) hierarchy_window->SetShowWindow();
				if (ImGui::MenuItem("Scene", nullptr, scene_window->GetShowWindow())) scene_window->SetShowWindow();
				if (ImGui::MenuItem("Inspector", nullptr, inspector_window->GetShowWindow())) inspector_window->SetShowWindow();
				if (ImGui::MenuItem("Explorer", nullptr, explorer_window->GetShowWindow())) explorer_window->SetShowWindow();
				if (ImGui::MenuItem("Resources", nullptr, resources_window->GetShowWindow())) resources_window->SetShowWindow();
				ImGui::MenuItem("Console", nullptr, &showConsoleWindow);
				ImGui::MenuItem("Engine Config", nullptr, &showConfigurationWindow);
				if (ImGui::MenuItem("Toolbar", nullptr, toolbar_window->GetShowWindow())) toolbar_window->SetShowWindow();
				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{			
			ImGui::MenuItem("Demo Window", nullptr, &showDemoWindow);
			if (ImGui::MenuItem("Documentation")) {
				ShellExecuteA(NULL, "open", "https://github.com/pablogalve/TurboX-Engine", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Download latest")) {
				ShellExecuteA(NULL, "open", "https://github.com/pablogalve/TurboX-Engine/releases", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Report a bug")) {
				ShellExecuteA(NULL, "open", "https://github.com/pablogalve/TurboX-Engine/issues", NULL, NULL, SW_SHOWNORMAL);
			}
			//ImGui::MenuItem("About", nullptr, &showAboutWindow);
			if (ImGui::MenuItem("About"))
				about_window->SetShowWindow();

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}