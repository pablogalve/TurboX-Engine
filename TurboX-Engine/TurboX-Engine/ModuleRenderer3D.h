#pragma once
#include "Module.h"
#include "ModuleImporter.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "Mesh_Cube.h"
#include "glew\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <array>
#include <cmath>
#include <vector>
#include "SceneWindow.h"

#pragma comment (lib, "Libraries/glew/glew32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

using namespace std;
#define MAX_LIGHTS 8

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Start()override;
	bool Init(JSON_Object* obj)override;
	update_status PreUpdate(float dt)override;
	update_status Update(float dt)override;
	update_status PostUpdate(float dt)override;
	bool CleanUp()override;

	void OnResize(int width, int height);

	void GL_Enable(unsigned int flag, bool active);
	void SetWireframeMode(bool active);

	void CreateGridLine(int size);
	void DrawGridLine();
	void DrawAxisLines();

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	bool _depth_test = false;
	bool _color_material = false;
	bool _cull_face = false;
	bool _lighting = false;
	bool _wireframe = false;
	bool _texture = false;

	GLuint frameBuffer;
	GLuint texColorBuffer;
	GLuint renderBuffer;
private:

	int grid_size;

	Mesh_Cube cube;
	Mesh_CustomMesh* house;
	SceneWindow* scene_window;
};