#include "Application.h"
#include "ModuleGui.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"


ModuleGui::ModuleGui(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Gui";
}

ModuleGui::~ModuleGui()
{}

bool ModuleGui::Start()
{
	bool ret = true;

	App->console->AddLog("Starting ImGui");
	//LOG("Starting ImGui");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable docking for multi viewports

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();

	// Setup style
	ImGui::StyleColorsDark();

	return ret;
}

update_status ModuleGui::PreUpdate(float dt)
{
	// Start the frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

update_status ModuleGui::Update(float dt)
{
	return UPDATE_CONTINUE;
}

void ModuleGui::Draw()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool ModuleGui::CleanUp()
{
	bool ret = true;

	App->console->AddLog("Cleaning up ImGui");
	//LOG("Cleaning up ImGui");

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return ret;
}