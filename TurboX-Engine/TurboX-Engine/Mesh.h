#pragma once
#include "Globals.h"
#include "glew\glew.h"
#include "SDL\include\SDL_opengl.h"
#include "DevIL/include/ilut.h"
#include "GameObject.h"
#include "glmath.h"
#include <list>
#include <vector>
#include <cmath>

#pragma comment (lib, "Libraries/glew/glew32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib,"Libraries/DevIL/lib/DevIL.lib")
#pragma comment (lib,"Libraries/DevIL/lib/ILUT.lib")
#pragma comment (lib,"Libraries/DevIL/lib/ILU.lib")

using namespace std;

class Mesh : public GameObject
{
public:
	Mesh();
	~Mesh();

	virtual void LoadTexture(const char* file_name);
	virtual void Draw();

	virtual void CreateMesh(std::string name);
	
public:
	ILuint ImageName;
	uint TextureID;

	GameObject* mesh;
};