#include <stdlib.h>
#include "Application.h"
#include "Globals.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "Libraries/SDL/libx86/SDL2.lib" )
#pragma comment( lib, "Libraries/SDL/libx86/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

int main(int argc, char ** argv)
{
	//LOG("Starting game '%s'...", TITLE);

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	Application* App = NULL;
	

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:
			if(App != nullptr)App->console->AddLog("-------------- Application Creation --------------");
			else //LOG("-------------- Application Creation --------------");
			App = new Application();
			state = MAIN_START;
			break;

		case MAIN_START:
			App->console->AddLog("-------------- Application Init --------------");
			//LOG("-------------- Application Init --------------");
			if (App->Init() == false)
			{
				App->console->AddLog("Application Init exits with ERROR");
				//LOG("Application Init exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				App->console->AddLog("-------------- Application Update --------------");
				//LOG("-------------- Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				App->console->AddLog("Application Update exits with ERROR");
				//LOG("Application Update exits with ERROR");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:
			App->console->AddLog("-------------- Application CleanUp --------------");
			//LOG("-------------- Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				App->console->AddLog("Application CleanUp exits with ERROR");
				//LOG("Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
	}
	delete App;
	//LOG("Exiting game '%s'...\n", TITLE);
	return main_return;
}