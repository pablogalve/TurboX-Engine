#pragma once
#include "Globals.h"
#include "glew\glew.h"
#include "SDL\include\SDL_opengl.h"
#include "glmath.h"
#include <list>
#include <vector>
#include <cmath>

#pragma comment (lib, "Libraries/glew/glew32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

using namespace std;

class Mesh
{
public:
	Mesh();
	~Mesh();

	virtual void Draw();
	
public:

	

};

