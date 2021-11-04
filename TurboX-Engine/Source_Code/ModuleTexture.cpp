#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "ModuleTexture.h"
#include "ModuleRenderer3D.h"
#include "ModuleFileSystem.h"
#include "Libraries/Devil/include/il.h"
#include "Libraries/Devil/include/ilut.h"
#include "Libraries/DevIL/include/ilu.h"
#include "Libraries\glew\glew.h"

#pragma comment (lib, "Libraries/glew/glew32.lib")
#pragma comment (lib, "Libraries/DevIL/lib/DevIL.lib")
#pragma comment (lib, "Libraries/DevIL/lib/ILUT.lib")
#pragma comment (lib, "Libraries/DevIL/lib/ILU.lib")


TextureImporter::TextureImporter(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "texture_importer";

	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
}


TextureImporter::~TextureImporter()
{
	ilShutDown();
}

bool TextureImporter::Start()
{
	return true;
}

update_status TextureImporter::Update(float dt)
{

	return UPDATE_CONTINUE;
}

bool TextureImporter::CleanUp()
{
	return true;
}



GLuint TextureImporter::LoadTexture(const char * path,uint &texWidth,uint &texHeight)
{
	MY_LOG("Loading Texture from %s", path);
	ILuint imageID;

	ilGenImages(1, &imageID); // generates an image
	ilBindImage(imageID);

	bool ret = ilLoadImage(path);
	if (ret) {

		ILinfo infoImage;
		iluGetImageInfo(&infoImage);

		if (infoImage.Origin == IL_ORIGIN_UPPER_LEFT)
			iluFlipImage();

		ret = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if (!ret) {
			MY_LOG("Cannot convert image. Error: %s", iluErrorString(ilGetError()))
				return -1;
		}

		GLuint textureID;
		texHeight = infoImage.Height;
		texWidth = infoImage.Width;
		
		glGenTextures(1, &textureID);//generates a texture buffer 
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		GLfloat maxAniso = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);//anisotropic Filter

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, infoImage.Width, infoImage.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData()); //specifies the texture

		ilDeleteImages(1, &imageID);

		glBindTexture(GL_TEXTURE_2D, textureID);
		
		return textureID;
	}
	else {

		MY_LOG("Cannot load texture from path. Error: %s", iluErrorString(ilGetError()))
			return -1;

	}
}

bool TextureImporter::ImportTexture(const char* tex, std::vector<std::string>* written, bool UI)
{
	bool ret = false;

	std::string extension;
	App->file_system->GetNameFromPath(tex, nullptr, nullptr, nullptr, &extension);
	if (extension != DDS_FORMAT)
		ret = App->texture_importer->ImportToDDS(tex, nullptr, written, UI);
	else
		ret = App->file_system->CopyDDStoLib(tex, written, UI);

	return ret;
}


bool TextureImporter::ImportToDDS( const char* texPath, const char* texName, std::vector<std::string>* written, bool UI ) {

	MY_LOG("Importing texture from %s", texPath);
	ILuint imageID;
	

	std::string textureName;
	std::string extension;
	if (texName == nullptr) {
		App->file_system->GetNameFromPath(texPath, nullptr, &textureName, nullptr, &extension);
	}
	else {
		textureName = texName;
		App->file_system->GetNameFromPath(texPath, nullptr, nullptr, nullptr, &extension);
	}
	
	

	ilGenImages(1, &imageID); // generates an image
	ilBindImage(imageID);

	bool ret = ilLoadImage(texPath);
	if (!ret) {
		MY_LOG("Cannot Load Texture from %s", texPath);
		ilDeleteImages(1, &imageID);		
	}
	else{
		
		ILuint size;
		ILubyte *data;		
		ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);// To pick a specific DXT compression use 
		size = ilSaveL(IL_DDS, NULL, 0); // gets the size of the data buffer
		if (size != 0) {
			data = new ILubyte[size]; // allocate data buffer
			if (ilSaveL(IL_DDS, data, size) > 0) // Save with the ilSaveIL function
			{
				MY_LOG("Imported succsfully into DDS");
				
				std::string uuid;
				std::string libPath;
				UI ? libPath = LIB_UI_PATH : libPath = LIB_TEXTURES_PATH;
				libPath += uuid + textureName + DDS_FORMAT;
				if (written) { (*written).push_back(libPath); }
				App->file_system ->writeFile(libPath.c_str(), data, size);
				ret = true;
			}
			delete[]data;
			

		}
		data = nullptr;
		ilDeleteImages(1, &imageID);		
	}
	return ret;
}

void TextureImporter::ManageDroppedTexture(const char * droppedFileDire)
{
	App->file_system->NormalizePath((char*)droppedFileDire);
	if (App->file_system->ExistsFile(droppedFileDire)) {
		MY_LOG("Texture already in Assets folder!")
	}
	else {
		std::string path = TEXTURES_PATH;
		std::string name;
		App->file_system->GetNameFromPath(droppedFileDire, nullptr, nullptr, &name, nullptr);
		path += name;
		App->file_system->Copy(droppedFileDire, path.c_str());
	}
	
}