#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "glew\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <array>
#include <cmath>
#include <vector>
#include "W_SceneWindow.h"
#include "Config_JSON.h"
#include "MathGeoLib/MathGeoLib.h"

#pragma comment (lib, "Libraries/glew/glew32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

using namespace std;
#define MAX_LIGHTS 8

class GameObject;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Start()override;
	bool Init()override;
	update_status PreUpdate(float dt)override;
	update_status Update(float dt)override;
	update_status PostUpdate(float dt)override;
	bool CleanUp()override;
	bool LoadSettings(Config* data)override;
	bool SaveSettings(Config* data)const override;

	void OnResize(int width, int height);

	void GL_Enable(unsigned int flag, bool active);
	void SetWireframeMode(bool active);

	void CreateGridLine(int size);
	void DrawGridLine();
	void DrawAxisLines();

	void CalculateGlobalMatrix(GameObject* gameObject);

	inline bool GetLoadFBXTest()const { return _loadFBXTest; }
public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	bool _depth_test;
	bool _color_material;
	bool _cull_face;
	bool _lighting;
	bool _wireframe;
	bool _texture;
	bool _loadFBXTest;
	bool changedFOV;
	bool ShowBB;
	bool ShowRayCast;

	GLuint frameBuffer;
	GLuint texColorBuffer;
	GLuint renderBuffer;
	
	//Clicking ray debug
	float3 clickA = float3::zero;
	float3 clickB = float3::zero;
private:
	int grid_size;

	W_SceneWindow* scene_window;
};