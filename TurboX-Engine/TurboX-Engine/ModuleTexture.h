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

	bool Start()override;
	bool Init(JSON_Object* obj)override;
	update_status PreUpdate(float dt)override;
	update_status PostUpdate(float dt)override;
	bool CleanUp()override;

public:
	GLuint frameBuffer;
	GLuint texColorBuffer;
	GLuint rboDepthStencil;

};
