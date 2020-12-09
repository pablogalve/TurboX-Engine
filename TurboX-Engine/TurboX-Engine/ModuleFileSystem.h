#ifndef __MODULE_FS_H__
#define __MODULE_FS_H__

#include "Module.h"
#include "Globals.h"

class ModuleFileSystem :
	public Module
{
public:
	ModuleFileSystem(Application* app, bool start_enabled = true);
	~ModuleFileSystem();

	bool addPath(const char* path);

	uint writeFile(const char* fileName, const void* data, uint bytes);
	uint readFile(const char* fileName, char** data);

	void RemoveFile(const char* path);

	bool CopyTURBOXtoLib(const char* path, std::vector<std::string>* written = nullptr, uint forceUUID = 0);

	void NormalizePath(char* full_path, bool toLower = false) const;

	void NormalizePath(std::string& full_path, bool toLower = false) const;

	bool Copy(const char* source, const char* destination);


	bool IsMetaFile(std::string file) const;
	uint GetLastModification(const char* file) const;
	void GetUUID_TURBOX(const char* fullName, std::string* uuid, std::string* turbox);

	void GetFilesFromDir(const char* directory, std::vector<std::string>& fileList, std::vector<std::string>& directoryList, bool recursive = false, bool ignoreMeta = false) const;

	void GetNameFromPath(const char* full_path, std::string* path, std::string* file, std::string* fileWithExtension, std::string* extension) const;
	void ShiftPath(std::string* path);
	bool ExistsFile(const char* path) const;
};

#endif // __MODULE_FS_H__