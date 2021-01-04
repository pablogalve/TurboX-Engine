#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	window = NULL;
	screen_surface = NULL;

	_fullscreen = false;
	_resizable = true;
	_borderless = false;
	_fullDesktop = false;

	width = 1024;
	height = 640;
	screen_size = 1;
	screen_margin_w = 100;
	screen_margin_h = 100;
	name = "Window";
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		MY_LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		SDL_DisplayMode desktopSize;
		SDL_GetDesktopDisplayMode(0, &desktopSize);
		width = desktopSize.w - screen_margin_w;
		height = desktopSize.h - screen_margin_h;

		//Create window
		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 3.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if(_fullscreen == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if(_resizable == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if(_borderless == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if(_fullDesktop == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(App->GetEngineName(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			MY_LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	OnResize(width * screen_size, height * screen_size);

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	MY_LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

bool ModuleWindow::LoadSettings(Config* data)
{
	/*SetBrightness(data->GetFloat("Brightness", DEFAULT_BRIGHTNESS));
	SetFullscreen(data->GetBool("Fullscreen", WIN_FULLSCREEN));
	SetResizable(data->GetBool("Resizable", WIN_RESIZABLE));
	SetBorderless(data->GetBool("Borderless", WIN_BORDERLESS));
	SetFullscreenDesktop(data->GetBool("Fullscreen Desktop", WIN_FULLSCREEN_DESKTOP));
	SetSize(data->GetUInt("Width", SCREEN_WIDTH), data->GetUInt("Height", SCREEN_HEIGHT));
	*/
	return true;
}

bool ModuleWindow::SaveSettings(Config* data) const
{
	data->AddFloat("Brightness", _brightness);
	data->AddBool("Fullscreen", _fullscreen);
	data->AddBool("Resizable", _resizable);
	data->AddBool("Borderless", _borderless);
	data->AddBool("Fullscreen Desktop", _fullDesktop);
	data->AddUInt("Width", width);
	data->AddUInt("Height", height);

	return true;
}

void ModuleWindow::SetTitle(const char* engine_name)
{
	SDL_SetWindowTitle(window, engine_name);
}

void ModuleWindow::SetBrightness(float bright)
{
	_brightness = bright;
	SDL_SetWindowBrightness(window, bright);
}

void ModuleWindow::SetSize(uint w, uint h)
{
	height = h;
	width = w;
	SDL_SetWindowSize(window, w, h);

}

void ModuleWindow::GetSize(int& w, int& h)const
{
	w = width;
	h = height;
}

void ModuleWindow::SetFullscreen(bool fullscreen) 
{

	Uint32 fullsFlag = fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_MINIMIZED;
	_fullscreen = fullscreen;
	SDL_SetWindowFullscreen(window, fullsFlag);
}

void ModuleWindow::SetResizable(bool resizable) 
{
	_resizable = resizable;
	SDL_bool res = SDL_bool(resizable);
	SDL_SetWindowResizable(window, res);
}
void ModuleWindow::SetBorderless(bool borderless) 
{
	_borderless = borderless;
	SDL_bool bord = SDL_bool(!borderless);
	SDL_SetWindowBordered(window, bord);
}

void ModuleWindow::SetFullscreenDesktop(bool fulldesktop) 
{
	_fullDesktop = fulldesktop;
	SDL_DisplayMode dMode;
	SDL_GetDesktopDisplayMode(0, &dMode);
	
	if (fulldesktop) 
	{
		SDL_SetWindowSize(window, dMode.w, dMode.h);
		SDL_SetWindowPosition(window, 0, 0);
	}
	else 
	{
		SDL_SetWindowSize(window, dMode.w / 2, dMode.h / 2);
		SDL_SetWindowPosition(window, dMode.w / 4, dMode.h / 4);
	}
}

void ModuleWindow::OnResize(int width, int height)
{
	this->width = width;
	this->height = height;
}