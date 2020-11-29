#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleConsole.h"
#include "GameObject.h"
#include "ModuleScene.h"
#include "ModuleEditor.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ModuleResources.h"
#define MAX_KEYS 300

ModuleInput::ModuleInput(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	keyboard = new KEY_STATE[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
	name = "Input";	
	dropped_filedir = nullptr;
}

// Destructor
ModuleInput::~ModuleInput()
{
	delete[] keyboard;
}

// Called before render is available
bool ModuleInput::Init()
{

	App->console->AddLog("Init SDL input event system");
	//LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		App->console->AddLog("SDL_Events could not initialize! SDL_Error: %s\n", SDL_GetError());
		//LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate(float dt)
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	
	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE) {
				keyboard[i] = KEY_DOWN;
			}
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

	mouse_x /= SCREEN_SIZE;
	mouse_y /= SCREEN_SIZE;
	mouse_z = 0;

	for(int i = 0; i < 5; ++i)
	{
		if(buttons & SDL_BUTTON(i))
		{
			if(mouse_buttons[i] == KEY_IDLE)
				mouse_buttons[i] = KEY_DOWN;
			else
				mouse_buttons[i] = KEY_REPEAT;
		}
		else
		{
			if(mouse_buttons[i] == KEY_REPEAT || mouse_buttons[i] == KEY_DOWN)
				mouse_buttons[i] = KEY_UP;
			else
				mouse_buttons[i] = KEY_IDLE;
		}
	}

	mouse_x_motion = mouse_y_motion = 0;
	
	bool quit = false;
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		ImGui_ImplSDL2_ProcessEvent(&e);

		switch(e.type)
		{
			case SDL_KEYDOWN:	
				AddLastInput("Keybr", e.key.keysym.sym, "KEY_DOWN");
			break;
			case SDL_KEYUP:
				AddLastInput("Keybr", e.key.keysym.sym, "KEY_UP");
			break;
			case SDL_MOUSEBUTTONDOWN:
				switch (e.button.button)
				{
				case SDL_BUTTON_LEFT:
					AddLastInput("Mouse", 0, "KEY_DOWN");
					break;
				case SDL_BUTTON_RIGHT:
					AddLastInput("Mouse", 2, "KEY_DOWN");
					break;
				default:
					AddLastInput("Mouse", 1, "KEY_DOWN");
					break;
				}
			break;
			case SDL_MOUSEBUTTONUP:
				switch (e.button.button)
				{
				case SDL_BUTTON_LEFT:
					AddLastInput("Mouse", 0, "KEY_UP");
					break;
				case SDL_BUTTON_RIGHT:
					AddLastInput("Mouse", 2, "KEY_UP");
					break;
				default:
					AddLastInput("Mouse", 1, "KEY_UP");
					break;
				}
				break;
			case SDL_MOUSEWHEEL:				
				mouse_z = e.wheel.y;
			break;

			case SDL_MOUSEMOTION:
				mouse_x = e.motion.x / SCREEN_SIZE;
				mouse_y = e.motion.y / SCREEN_SIZE;

				mouse_x_motion = e.motion.xrel / SCREEN_SIZE;
				mouse_y_motion = e.motion.yrel / SCREEN_SIZE;
			break;

			case SDL_QUIT:
			quit = true;
			break;

			case (SDL_DROPFILE): 
			{      
				// In case if dropped file
				dropped_filedir = e.drop.file;

				FileType fileType = GetFileType(dropped_filedir);

				switch (fileType)
				{
				case FileType::FBX:
					App->resources->ImportFileFromAssets(dropped_filedir);
					break;
				case FileType::PNG:
				{
					if (App->editor->hierarchy_window->selectedGameObjects.empty() == false) {
						GameObject* selectedGameObject = App->editor->hierarchy_window->selectedGameObjects[0];
						if (selectedGameObject != nullptr)
						{
							if (selectedGameObject->material == nullptr) {
								selectedGameObject->CreateComponent(Component::Type::Material);
								selectedGameObject->material->LoadTexture(dropped_filedir);
							}
							else {
								//TODO: Remove current texture
								selectedGameObject->material->LoadTexture(dropped_filedir);
							}
						}
					}
					else {
						App->console->AddLog("You must select a gameObject first!");
					}
				}
					break;
				case FileType::DDS:
				{
					if (App->editor->hierarchy_window->selectedGameObjects.empty() == false) {
						GameObject* selectedGameObject = App->editor->hierarchy_window->selectedGameObjects[0];
						if (selectedGameObject != nullptr)
						{
							if (selectedGameObject->material == nullptr) {
								selectedGameObject->CreateComponent(Component::Type::Material);
								selectedGameObject->material->LoadTexture(dropped_filedir);
							}
							else {
								//TODO: Remove current texture
								selectedGameObject->material->LoadTexture(dropped_filedir);
							}							
						}
					}
					else {
						App->console->AddLog("You must select a gameObject first!");
					}
				}
					break;
				case FileType::UNDEFINED:
					break;
				default:
					break;
				}				
				
				break;
			}
			case SDL_WINDOWEVENT:
			{
				if(e.window.event == SDL_WINDOWEVENT_RESIZED)
					App->renderer3D->OnResize(e.window.data1, e.window.data2);
			}
		}
	}

	if(quit == true || keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	App->console->AddLog("Quitting SDL input event subsystem");
	//LOG("Quitting SDL input event subsystem");
	SDL_free(dropped_filedir);
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

void ModuleInput::AddLastInput(std::string name, Uint8 keyboard_num, std::string type)
{
	if (last_inputs->last_input == last_inputs->size - 1) {
		//List is full

		for (int j = 0; j < last_inputs->size - 1; j++)
		{
			//We remove the first input(last_input[0]) and move everything up to make space for the new element
			last_inputs[j].name = last_inputs[j + 1].name;
			last_inputs[j].keyboard_num = last_inputs[j + 1].keyboard_num;
			last_inputs[j].type = last_inputs[j + 1].type;
			//last_inputs[i] = last_inputs[i + 1];
		}

		//We add the last input to the list
		last_inputs[last_inputs->last_input].name = name;
		last_inputs[last_inputs->last_input].keyboard_num = keyboard_num;
		last_inputs[last_inputs->last_input].type = type;
		last_inputs[last_inputs->last_input].is_null = false;

		//last_inputs[last_inputs->size].is_null = true;		
	}
	else {
		//List is not full

		//We add the last input to the list
		last_inputs[last_inputs->last_input].name = name;
		last_inputs[last_inputs->last_input].keyboard_num = keyboard_num;
		last_inputs[last_inputs->last_input].type = type;
		last_inputs[last_inputs->last_input].is_null = false;

		if(last_inputs->last_input < last_inputs->size - 1)
			last_inputs->last_input++;
	}
}

void ModuleInput::PrintLastInputs()
{
	//Name: keyboard_num - Type
	/*Output Examples:
		Keybr: 93 - UP
		Mouse: 02 - REPEAT
	*/
	for (int i = last_inputs->size; i >= 0; i--)
	{
		if (last_inputs[i].is_null == false) {
			std::string _name = last_inputs[i].name;
			int _keyboard_num = (int)(last_inputs[i].keyboard_num);
			std::string _type = last_inputs[i].type;

			//ImGui::Text("%s: %i - %s", _name, _keyboard_num, _type);
			ImGui::Text("%s: %i - %s", _name.c_str(), _keyboard_num, _type.c_str());
		}
	}	
}

FileType ModuleInput::GetFileType(std::string file)
{
	if (file.length() > 4) {
		std::string extensionType = file.substr(file.length() - 4);

		if (extensionType == ".fbx" || extensionType == ".FBX")
			return FileType::FBX;
		else if (extensionType == ".png" || extensionType == ".PNG")
			return FileType::PNG;
		else if (extensionType == ".dds" || extensionType == ".DDS")
			return FileType::DDS;
		else {
			return FileType::UNDEFINED;
			App->console->AddLog("Error. Format is not supported in the engine.");
		}
	}
	else {
		return FileType::UNDEFINED;
		App->console->AddLog("Error. Can't recognize format.");
	}
	
}
