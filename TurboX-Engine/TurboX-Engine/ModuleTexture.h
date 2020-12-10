#ifndef __TEXTUREIMPORTER_H__
#define __TEXTUREIMPORTER_H__

#include "Module.h"
#include "Globals.h"
#include "Component_Material.h"

struct ComponentMaterial;

class TextureImporter : public Module
{
public:
	TextureImporter(Application* app, bool start_enabled = true);
	~TextureImporter();

	bool Start()override;
	update_status Update(float dt)override;
	bool CleanUp()override;

	bool ImportToDDS(const char * texPath, const char* texName = nullptr, std::vector<std::string>* written = nullptr, bool UI = false);

	
	GLuint LoadTexture(const char* path,  uint &texWidth, uint &texHeight);

	bool ImportTexture(const char * tex, std::vector<std::string>* written, bool UI = false);

	void ReceiveEvent(const Event &event);


public: 
	
	uint imageID = 0;

private:
	void ManageDroppedTexture(const char * droppedFileDire);

	
};

#endif //__TEXTUREIMPORTER_H__


