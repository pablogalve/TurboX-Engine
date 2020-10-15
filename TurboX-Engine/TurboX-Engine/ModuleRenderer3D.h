#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include <array>

using namespace std;
#define MAX_LIGHTS 8

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Start();
	bool Init(JSON_Object* obj);
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();


	void OnResize(int width, int height);

	void GL_Enable(unsigned int flag, bool active);
	void SetWireframeMode(bool active);
	void DrawCubeWithDirectMode();
	void DrawCubeWithArrays();
	void DrawCubeWithIndices();
	void DrawPyramid();
	void DrawSphere();

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	bool _cull_face = false;
	bool _lighting = false;
	bool _wireframe = false;


};