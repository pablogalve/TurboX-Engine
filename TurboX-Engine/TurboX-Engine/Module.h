#pragma once

#include "./JSON/parson.h"
#include <string>
#include "Config_JSON.h"

class Application;

class Module
{
private :
	bool enabled;

public:
	
	Application* App;

	std::string name;

	Module(Application* parent, bool start_enabled = true) : App(parent)
	{}

	virtual ~Module()
	{}

	virtual bool Init()
	{
		return true; 
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}

	virtual bool LoadSettings(Config* data) 
	{
		return true;
	}
	virtual bool SaveSettings(Config* data) const
	{
		return true;
	}
};