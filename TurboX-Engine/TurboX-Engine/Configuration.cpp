#include "Configuration.h"

Configuration::Configuration(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	fps_log.resize(100);
	ms_log.resize(100);
	caps_log.resize(0);
}

Configuration::~Configuration()
{
}

void Configuration::Draw()
{
	ImGui::Begin("Configuration");

	ImGui::Text("Options");

	ImVec4 yellow(1.0f, 0.8f, 0.0f, 1.0f); //We'll use yellow to print the results

	if (ImGui::CollapsingHeader("Application"))
	{
		char appName[50] = "TurboX Engine";
		char appName2[50];


		if (ImGui::InputText("App name", appName, 50, ImGuiInputTextFlags_EnterReturnsTrue)) {
			int fd = 5;
		}
		ImGui::InputText("Organization", "UPC CITM", 50);

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
		char filename[] = "../../../../TurboX-Engine";
		char fullFilename[MAX_PATH];

		GetFullPathName(filename, MAX_PATH, fullFilename, nullptr);

		ImGui::Text("Base Path: ");
		ImGui::TextColored(yellow, fullFilename);
	}
	if (ImGui::CollapsingHeader("Input"))
	{
		//Mouse position
		POINT cursor_position;
		if (GetCursorPos(&cursor_position)) {
			ImGui::Text("Mouse Position: "); ImGui::SameLine();
			ImGui::TextColored(yellow, "%i, %i", cursor_position.x, cursor_position.y);
		}

		//Mouse motion
		ImGui::Text("Mouse Motion: "); ImGui::SameLine();
		ImGui::TextColored(yellow, "%i, %i", App->input->GetMouseXMotion(), App->input->GetMouseYMotion());

		//Mouse Wheel
		ImGui::Text("Mouse Wheel: "); ImGui::SameLine();
		ImGui::TextColored(yellow, "%i", App->input->GetMouseZ());

		ImGui::Separator();

		ImGui::Text("Last Inputs:");
		App->input->PrintLastInputs();

		ImGui::Separator();
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
		GetHardwareCaps();

		//SDL Version
		SDL_version sdl_version;
		SDL_GetVersion(&sdl_version);
		ImGui::Text("SDL Version:");
		ImGui::SameLine();
		ImGui::TextColored(yellow, "%d.%d.%d", sdl_version.major, sdl_version.minor, sdl_version.patch);
		ImGui::Separator();

		//CPUs
		ImGui::Text("CPUs: ");
		ImGui::SameLine();
		ImGui::TextColored(yellow, "%i (Cache: %ikb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());

		//System RAM		
		float ram_gb = (float)(SDL_GetSystemRAM()); //We get the RAM in megabytes so we convert it to gigabytes
		ImGui::Text("System RAM: ");
		ImGui::SameLine();
		ImGui::TextColored(yellow, "%.2f GB", ram_gb / 1024);

		//Caps		
		ImGui::Text("Caps: ");
		for (int i = 0; i < caps_log.size(); i++)
		{
			if (i != 4)
				ImGui::SameLine();
			ImGui::TextColored(yellow, "%s,", caps_log[i].c_str());
		}
		caps_log.clear();
		ImGui::Separator();

		//GPU
		ImGui::Text("GPU: ");
		ImGui::SameLine();
		ImGui::TextColored(yellow, "%s", glGetString(GL_RENDERER));

		//Brand
		ImGui::Text("Brand: ");
		ImGui::SameLine();
		ImGui::TextColored(yellow, "%s", glGetString(GL_VENDOR));

		//VRAM
		float vram_budget = 0, vram_usage = 0, vram_available = 0, vram_reserved = 0;

		GetVramData(vram_budget, vram_usage, vram_available, vram_reserved);

		ImGui::Text("VRAM Total: ");
		ImGui::SameLine();
		ImGui::TextColored(yellow, "%.1f Mb", vram_budget);

		ImGui::Text("VRAM Dedicated: ");
		ImGui::SameLine();
		ImGui::TextColored(yellow, "%.1f Mb", vram_usage);

		ImGui::Text("VRAM Available: ");
		ImGui::SameLine();
		ImGui::TextColored(yellow, "%.1f Mb", vram_available);

		ImGui::Text("VRAM Reserved: ");
		ImGui::SameLine();
		ImGui::TextColored(yellow, "%.1f Mb", vram_reserved);
	}
	if (ImGui::CollapsingHeader("Renderer"))
	{
		if (ImGui::Checkbox("Cull Face", &App->renderer3D->_cull_face))
		{
			App->renderer3D->GL_Enable(GL_CULL_FACE, App->renderer3D->_cull_face);
		}
		if (ImGui::Checkbox("Lighting", &App->renderer3D->_lighting))
		{
			App->renderer3D->GL_Enable(GL_LIGHTING, App->renderer3D->_lighting);
		}
		if (ImGui::Checkbox("Wireframe", &App->renderer3D->_wireframe))
		{
			App->renderer3D->SetWireframeMode(App->renderer3D->_wireframe);
		}
		if (ImGui::Checkbox("Texture", &App->renderer3D->_texture))
		{
			App->renderer3D->GL_Enable(GL_TEXTURE_2D, App->renderer3D->_texture);
		}
		if (ImGui::Checkbox("Depth test", &App->renderer3D->_depth_test))
		{
			App->renderer3D->GL_Enable(GL_DEPTH_TEST, App->renderer3D->_depth_test);
		}
		if (ImGui::Checkbox("Color material", &App->renderer3D->_color_material))
		{
			App->renderer3D->GL_Enable(GL_COLOR_MATERIAL, App->renderer3D->_color_material);
		}
	}

	ImGui::End();
}

void Configuration::SetShowWindow()
{
	showWindow = !showWindow;
}

void Configuration::GetHardwareCaps()
{
	if (SDL_Has3DNow())caps_log.push_back("3DNow");
	if (SDL_HasAVX())caps_log.push_back("AVX");
	if (SDL_HasAVX2())caps_log.push_back("AVX2");
	if (SDL_HasAltiVec())caps_log.push_back("AltiVec");
	if (SDL_HasMMX())caps_log.push_back("MMX");
	if (SDL_HasRDTSC())caps_log.push_back("RDTSC");
	if (SDL_HasSSE())caps_log.push_back("SSE");
	if (SDL_HasSSE2())caps_log.push_back("SSE2");
	if (SDL_HasSSE3())caps_log.push_back("SSE3");
	if (SDL_HasSSE41())caps_log.push_back("SSE41");
	if (SDL_HasSSE42())caps_log.push_back("SSE42");
}

void Configuration::GetVramData(float& vram_budget, float& vram_usage, float& vram_available, float& vram_reserved)
{
	// NVIDIA Documentation:
	// http://developer.download.nvidia.com/opengl/specs/GL_NVX_gpu_memory_info.txt
	// ATI Technologies Documentation:
	// https://www.khronos.org/registry/OpenGL/extensions/ATI/ATI_meminfo.txt

	const char* gpu_brand = (const char*)(glGetString(GL_VENDOR));
	GLint _vram_budget;
	GLint _vram_usage;
	GLint _vram_available;
	GLint _vram_reserved;

	if (strcmp(gpu_brand, "0x0423fc58") || strcmp(gpu_brand, "NVIDIA Corporation")) { //NVIDIA Corporation
		glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &_vram_budget); //total available memory, total size (in Kb) of the memory available for allocations
		glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &_vram_usage); //dedicated video memory, total size (in kb) of the GPU memory		
		glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &_vram_available); //current available dedicated video memory (in kb), currently unused GPU memory
		glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX, &_vram_reserved); //size of total video memory evicted (in kb)

		//We convert our local GLint variables into float variables
		//At the same time -> Data is returned in kb, so we convert it into Mb
		vram_budget = (float)(_vram_budget / 1024);
		vram_usage = (float)(_vram_usage / 1024);
		vram_available = (float)(_vram_available / 1024);
		vram_reserved = (float)(_vram_reserved / 1024);
	}
	else if (strcmp(gpu_brand, "ATI Technologies")) {
		//TODO
	}
}
