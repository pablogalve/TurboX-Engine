#ifndef __ModuleImporter_H__
#define __ModuleImporter_H__

#include "Application.h"


class ModuleImporter : public Module
{
public:

	ModuleImporter(Application* app, bool start_enabled = true);
	~ModuleImporter();

	bool Init(JSON_Object* obj);
	bool CleanUp();

private:


};

#endif // __ModuleImporter_H__
