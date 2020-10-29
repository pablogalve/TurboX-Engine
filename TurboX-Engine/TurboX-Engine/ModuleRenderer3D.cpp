#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleConsole.h"
#include "ModuleGui.h"
#include "ModuleScene.h"

ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	_depth_test = true;
	_color_material = true;
	_cull_face = true;
	_lighting = false;
	_wireframe = false;
	_texture = true;
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

bool ModuleRenderer3D::Start()
{
	bool ret = true;
	
	CreateGridLine(100);

	return ret;
}

// Called before render is available
bool ModuleRenderer3D::Init(JSON_Object* obj)
{
	App->console->AddLog("Creating 3D Renderer context");
	//LOG("Creating 3D Renderer context");
	bool ret = true;

	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if (context == NULL)
	{
		App->console->AddLog("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		//LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	GLenum error = glewInit();

	if (ret == true)
	{
		//Use Vsync
		if (VSYNC && SDL_GL_SetSwapInterval(1) < 0){
			App->console->AddLog("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
		//LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
		}

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			App->console->AddLog("Error initializing OpenGL! %s\n", __glewErrorStringREGAL(error));
			//LOG("Error initializing OpenGL! %s\n", __glewErrorStringREGAL(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			App->console->AddLog("Error initializing OpenGL! %s\n", __glewErrorStringREGAL(error));
			//LOG("Error initializing OpenGL! %s\n", __glewErrorStringREGAL(error));
			ret = false;
		}

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);

		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			App->console->AddLog("Error initializing OpenGL! %s\n", __glewErrorStringREGAL(error));
			//LOG("Error initializing OpenGL! %s\n", __glewErrorStringREGAL(error));
			ret = false;
		}

		GLfloat LightModelAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);

		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();

		GLfloat MaterialAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glDisable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
		
	}

	//FrameBuffer
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	//Texture Buffer
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, App->window->_w, App->window->_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

	//RenderBuffer
	glGenRenderbuffers(1, &renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, App->window->_w, App->window->_h);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		App->console->AddLog("Scene Framebuffer is not complete");
	else
		App->console->AddLog("Framebuffer is completed");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	json_object_clear(obj);
	return ret;
}
// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for (uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	return UPDATE_CONTINUE;
}

update_status ModuleRenderer3D::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	//App->importer->ourMesh.Draw();
	//cube.Draw();

	return ret;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	DrawGridLine();
	DrawAxisLines();

	//new_gameObject->Draw();
	//TODO: Now it's drawing from a C_Mesh. We need to change it to a GameObject
	//house->Draw();

	//App->scene->DrawGameObjects(App->scene->GetRoot(), App->scene->GetRoot());

	glBindVertexArray(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	App->gui->Draw();
	
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	App->console->AddLog("Destroying 3D Renderer");
	//LOG("Destroying 3D Renderer");
	glDeleteFramebuffers(1, &frameBuffer);
	SDL_GL_DeleteContext(context);

	return true;
}

void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ModuleRenderer3D::GL_Enable(unsigned int flag, bool active)
{
	if (active)
		glEnable(flag);
	else
		glDisable(flag);
}

void ModuleRenderer3D::SetWireframeMode(bool active) 
{
	if (active)glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ModuleRenderer3D::CreateGridLine(int size = 1000)
{
	grid_size = size;	
}

void ModuleRenderer3D::DrawGridLine()
{
	glBegin(GL_LINES);

	//Vertical Lines
	for (float x = -grid_size * 0.5f; x <= grid_size * 0.5f; x++)
	{
		glVertex3f(x, 0, -grid_size * 0.5f); glVertex3f(x, 0, grid_size * 0.5f);
	}

	//Horizontal Lines
	for (float z = -grid_size * 0.5f; z <= grid_size * 0.5f; z++)
	{
		glVertex3f(-grid_size * 0.5f, 0, z); glVertex3f(grid_size * 0.5f, 0, z);
	}

	glEnd();
}

void ModuleRenderer3D::DrawAxisLines()
{
	glPushMatrix();
	
	// Draw Axis Grid
	glLineWidth(2.0f);

	glBegin(GL_LINES);

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); // Sex color of x axis to red

	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
	glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // Sex color of y axis to green

	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.0f, 1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Sex color of z axis to blue

	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.05f, 0.1f, 1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
	glVertex3f(0.05f, 0.1f, 1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
	glVertex3f(-0.05f, -0.1f, 1.05f); glVertex3f(0.05f, -0.1f, 1.05f);

	glEnd();

	glLineWidth(1.0f);	

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Set color of everything back to white
	glPopMatrix();
}

