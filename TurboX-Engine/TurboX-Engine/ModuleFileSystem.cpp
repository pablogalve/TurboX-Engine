#include "Application.h"
#include "ModuleFileSystem.h"
#include "PhysFS/include/physfs.h"


#pragma comment( lib, "Libraries/PhysFS/libx86/physfs.lib" )

ModuleFileSystem::ModuleFileSystem(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "FileSystem";

	char* base_path = SDL_GetBasePath();
	PHYSFS_init(base_path);
	SDL_free(base_path);

	if (PHYSFS_setWriteDir(".") == 0)
		MY_LOG("File System error while creating write dir: %s\n", PHYSFS_getLastError());

	addPath(".");

	const char* mainPaths[] = {
		MODELS_PATH, TEXTURES_PATH, AUDIO_PATH, LIB_MODELS_PATH, LIB_TEXTURES_PATH, SETTINGS_PATH
	};
	for (uint i = 0; i < NUM_PATHS; ++i)
	{
		if (PHYSFS_exists(mainPaths[i]) == 0)
			PHYSFS_mkdir(mainPaths[i]);

		addPath(mainPaths[i]);
	}
}


ModuleFileSystem::~ModuleFileSystem()
{
}

bool ModuleFileSystem::addPath(const char* path)
{
	bool ret = true;

	if (PHYSFS_mount(path, nullptr, 1) == 0) {
		MY_LOG("File System error while adding a path: %s\n", PHYSFS_getLastError());
		ret = false;
	}
	return ret;
}

uint ModuleFileSystem::writeFile(const char* fileName, const void* data, uint bytes)
{
	PHYSFS_file* file = PHYSFS_openWrite(fileName);
	if (file == nullptr)
	{
		MY_LOG("Error opening file. Error:", PHYSFS_getLastError());
		return 0;
	}
	else {

		uint written = PHYSFS_write(file, (const void*)data, 1, bytes);
		PHYSFS_close(file);

		if (written != bytes)
		{
			MY_LOG("Writting file error. Not all data readen Error:  %s", PHYSFS_getLastError());
			return 0;
		}

		return written;
	}


}

uint ModuleFileSystem::readFile(const char* fileName, char** data)
{
	NormalizePath((char*)fileName);
	PHYSFS_file* file = PHYSFS_openRead(fileName);
	uint ret = 0;

	if (file != nullptr)
	{
		PHYSFS_sint32 size = (PHYSFS_sint32)PHYSFS_fileLength(file);

		if (size > 0)
		{
			*data = new char[size];
			uint readed = (uint)PHYSFS_read(file, *data, 1, size);

			if (readed != size)
			{
				MY_LOG("File System error while reading from file %s: %s\n", file, PHYSFS_getLastError());
				PHYSFS_close(file);
				return ret;
			}
			else

				ret = readed;
		}

	}
	else
		MY_LOG("File System error while opening file %s: %s\n", file, PHYSFS_getLastError());
	PHYSFS_close(file);
	return ret;
}

void ModuleFileSystem::RemoveFile(const char* path)
{
	remove(path);
}

bool ModuleFileSystem::CopyTURBOXtoLib(const char* path, std::vector<std::string>* written, uint forceUUID)
{
	bool ret = false;
	std::string turboxName;
	GetNameFromPath(path, nullptr, &turboxName, nullptr, nullptr);

	std::string uuid;
	if (forceUUID != 0) { uuid += std::to_string(forceUUID) + "~"; }

	std::string libpath = LIB_MODELS_PATH + uuid + turboxName + DDS_FORMAT;
	if (written) { (*written).push_back(libpath); }
	if (ExistsFile(libpath.c_str())) { return true; }
	ret = Copy(path, libpath.c_str());

	return ret;
}


void ModuleFileSystem::GetUUID_TURBOX(const char* fullName, std::string* uuid, std::string* turbox)
{
	if (fullName != nullptr) {
		std::string UUIDTURBOXName = fullName;
		uint posLow = UUIDTURBOXName.find_first_of("~");
		if (uuid) {
			*uuid = UUIDTURBOXName.substr(0, posLow - 1);
			UUIDTURBOXName = fullName;
		}
		if (turbox)
			*turbox = UUIDTURBOXName.substr(posLow + 1);
	}
}

void ModuleFileSystem::GetNameFromPath(const char* full_path, std::string* path, std::string* file, std::string* fileWithExtension, std::string* extension) const
{
	if (full_path != nullptr)
	{
		std::string nwFullPath = full_path;
		NormalizePath(nwFullPath);
		size_t posSlash = nwFullPath.find_last_of("\\/");
		size_t posDot = nwFullPath.find_last_of(".");

		if (path != nullptr)
		{
			if (posSlash < nwFullPath.length())
				*path = nwFullPath.substr(0, posSlash + 1);
			else
				path->clear();
		}
		if (fileWithExtension != nullptr) {
			if (posSlash < nwFullPath.length()) {
				*fileWithExtension = nwFullPath.substr(posSlash + 1);
			}
			else
				*fileWithExtension = nwFullPath;
		}

		if (file != nullptr)
		{
			nwFullPath = nwFullPath.substr(0, posDot);
			posSlash = nwFullPath.find_last_of("\\/");
			*file = nwFullPath.substr(posSlash + 1);

		}

		if (extension != nullptr)
		{
			if (posDot < nwFullPath.length())
				*extension = nwFullPath.substr(posDot);
			else
				extension->clear();
		}
	}

}

void ModuleFileSystem::ShiftPath(std::string* path)
{
	std::string fullpath = *path;
	uint posSlash = fullpath.find_last_of("/");

	if (fullpath.size() > posSlash) {
		if (fullpath.size() - posSlash == 1) {
			fullpath = fullpath.substr(0, posSlash).c_str();
			posSlash = fullpath.find_last_of("/");
			if (posSlash > fullpath.size()) {
				return;
			}
		}
		*path = fullpath.substr(0, posSlash + 1).c_str();
	}

}

bool ModuleFileSystem::ExistsFile(const char* path) const {

	bool ret = PHYSFS_exists(path);
	return ret;
}

void ModuleFileSystem::NormalizePath(char* full_path, bool toLower) const
{
	uint len = strlen(full_path);
	for (int i = 0; i < len; ++i)
	{
		if (full_path[i] == '\\')
			full_path[i] = '/';
		else
			if (toLower) {
				full_path[i] = tolower(full_path[i]);
			}
	}
}
void ModuleFileSystem::NormalizePath(std::string& full_path, bool toLower) const
{
	for (std::string::iterator charIterator = full_path.begin(); charIterator != full_path.end(); ++charIterator)
	{
		if (*charIterator == '\\')
			*charIterator = '/';
		else
			if (toLower) {
				*charIterator = tolower(*charIterator);
			}
	}
}

bool ModuleFileSystem::Copy(const char* source, const char* destination) //copy outside virtual filesystem
{
	bool ret = false;
	const uint def_size = 8192;
	char buf[def_size];


	FILE* src = nullptr;
	fopen_s(&src, source, "rb");
	PHYSFS_file* dest = PHYSFS_openWrite(destination);

	PHYSFS_sint32 size;
	if (src && dest) {

		while (size = fread_s(buf, def_size, 1, def_size, src))
			PHYSFS_write(dest, buf, 1, size);

		fclose(src);
		PHYSFS_close(dest);
		ret = true;

		MY_LOG("Copied file from %s to %s", source, destination);
	}
	else
		MY_LOG("Error copying file from %s to %s", source, destination);

	return ret;
}

bool ModuleFileSystem::IsMetaFile(std::string file) const
{
	if (file.size() > 5) {

		if (file.substr(file.size() - 5) == META_FORMAT) {
			return true;
		}
	}

	return false;
}

uint ModuleFileSystem::GetLastModification(const char* file) const
{
	struct stat result;
	if (stat(file, &result) == 0) {
		return  result.st_mtime;

	}
	return 0;
}


void ModuleFileSystem::GetFilesFromDir(const char* directory, std::vector<std::string>& files, std::vector<std::string>& directories, bool recursive, bool ignoreMeta) const
{
	char** filesInDir = PHYSFS_enumerateFiles(directory);
	char** filePointer;

	std::string dir = directory;

	for (filePointer = filesInDir; *filePointer != nullptr; filePointer++)
	{
		if (PHYSFS_isDirectory((dir + *filePointer).c_str())) {
			std::string dire = *filePointer;
			dire += "/";
			directories.push_back(dire);
		}
		else {
			std::string file = directory;
			file += *filePointer;
			if (ignoreMeta) {
				if (IsMetaFile(file)) {
					continue;
				}
			}
			files.push_back(file.c_str());
		}
	}
	if (recursive && directories.size() > 0) {
		std::vector<std::string> newDirs;
		for (int i = 0; i < directories.size(); i++) {
			std::string dir = directory + directories[i];
			GetFilesFromDir(dir.c_str(), files, newDirs);
			if (newDirs.size() > 0) {
				for (int j = newDirs.size() - 1; j >= 0; j--) {
					directories.push_back(directories[i] + newDirs[j]);
					newDirs.pop_back();
				}
			}
		}
	}
	PHYSFS_freeList(filesInDir);
}