#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	window = NULL;
	screen_surface = NULL;

	_fullscreen = WIN_FULLSCREEN;
	_resizable = WIN_RESIZABLE;
	_borderless = WIN_BORDERLESS;
	_fullDesktop = WIN_FULLSCREEN_DESKTOP;

	_w = SCREEN_WIDTH;
	_h = SCREEN_HEIGHT;

	name = "Window";
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	//LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		int width = _w * SCREEN_SIZE;
		int height = _h * SCREEN_SIZE;
		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

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

		window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			//LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	//LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::SetTitle(const char* title)
{
	_title = title;
	SDL_SetWindowTitle(window, title);
}

void ModuleWindow::SetBrightness(float bright)
{
	_brightness = bright;
	SDL_SetWindowBrightness(window, bright);
}

void ModuleWindow::SetSize(uint w, uint h)
{
	_h = h * SCREEN_SIZE;
	_w = w * SCREEN_SIZE;
	SDL_SetWindowSize(window, w, h);

}

void ModuleWindow::GetSize(int& w, int& h)const
{
	w = _w;
	h = _h;
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