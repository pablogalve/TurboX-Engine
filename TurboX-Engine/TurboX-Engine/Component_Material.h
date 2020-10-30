#ifndef __COMPONENT_MATERIAL_H_
#define __COMPONENT_MATERIAL_H_

#include "Component.h"
#include "glew\glew.h"
#include "DevIL/include/ilut.h"
#include <string>

#pragma comment (lib, "Libraries/glew/glew32.lib") /* link OpenGL Utility lib */
#pragma comment (lib, "Libraries/DevIL/lib/DevIL.lib")
#pragma comment (lib, "Libraries/DevIL/lib/ILUT.lib")
#pragma comment (lib, "Libraries/DevIL/lib/ILU.lib")

using namespace std;

class C_Material : public Component {
public:
	C_Material(Component::Type type, GameObject* owner);
	~C_Material();

	void LoadTexture(const char* file_name);
	void UnLoadTexture();
	void LoadDefaultTex();
	
	string GetMaterialPath() { return material_path; }
public:

	Component::Type GetComponentType() override;

public:	
	ILuint imageName;
	ILuint checkersImage;
	uint textureID;
	uint defaultTextureID;

	bool defaultTex;
private:
	string material_path;
};
#endif // !__COMPONENT_MATERIAL_H_
