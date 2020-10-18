#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleTexture.h"
#include "SDL\include\SDL_opengl.h"

#pragma comment (lib, "Libraries/glew/glew32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleTexture::ModuleTexture(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

// Destructor
ModuleTexture::~ModuleTexture()
{}

bool ModuleTexture::Start()
{
	
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);

	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(
		GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0
	);

	glGenRenderbuffers(1, &rboDepthStencil);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepthStencil);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT);//screen width & screen height

	glFramebufferRenderbuffer(
		GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepthStencil
	);
	
	bool ret = true;

	return ret;
}

// Called before render is available
bool ModuleTexture::Init(JSON_Object* obj)
{
	bool ret = true;
	json_object_clear(obj);
	return ret;
}
// PreUpdate: clear buffer
update_status ModuleTexture::PreUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleTexture::PostUpdate(float dt)
{
	/*glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	*/
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleTexture::CleanUp()
{
	//glDeleteFramebuffers(1, &frameBuffer);

	return true;
}