#ifndef __COMPONENT_MATERIAL_H_
#define __COMPONENT_MATERIAL_H_

#include "Component.h"
#include "glew\glew.h"
#include "SDL\include\SDL_opengl.h"
#include "DevIL/include/ilut.h"

#pragma comment (lib, "Libraries/glew/glew32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib,"Libraries/DevIL/lib/DevIL.lib")
#pragma comment (lib,"Libraries/DevIL/lib/ILUT.lib")
#pragma comment (lib,"Libraries/DevIL/lib/ILU.lib")

class C_Material : public Component {
public:
	C_Material(Component::Type type, GameObject* owner);
	~C_Material();

	void LoadTexture(const char* file_name);

public:

	Component::Type GetComponentType() override;

public:
	
	ILuint ImageName;
	uint TextureID;
};
#endif // !__COMPONENT_MATERIAL_H_
