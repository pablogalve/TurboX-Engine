#include <stdlib.h>
#include "Application.h"
#include "Globals.h"
#include "ModuleConsole.h"

#include "Libraries/SDL/include/SDL.h"
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

Application* App = NULL;

int main(int argc, char ** argv)
{
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	
	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:
			if(App != nullptr)
				MY_LOG("-------------- Application Creation --------------");
			App = new Application();
			state = MAIN_START;
			break;

		case MAIN_START:
			MY_LOG("-------------- Application Init --------------");
			if (App->Init() == false)
			{
				MY_LOG("Application Init exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				MY_LOG("-------------- Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				MY_LOG("Application Update exits with ERROR");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:
			MY_LOG("-------------- Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				MY_LOG("Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
	}
	delete App;
	return main_return;
}