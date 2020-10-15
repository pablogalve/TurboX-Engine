#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include <array>
#include "glew\glew.h"

using namespace std;
#define MAX_LIGHTS 8

class ModuleTexture : public Module
{
public:
	ModuleTexture(Application* app, bool start_enabled = true);
	~ModuleTexture();

	bool Start();
	bool Init(JSON_Object* obj);
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();


public:
	GLuint frameBuffer;
	GLuint texColorBuffer;
	GLuint rboDepthStencil;

};
