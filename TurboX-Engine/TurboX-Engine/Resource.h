#pragma once

#include "Globals.h"

enum class ResourceType;

class Resource
{

public:
	Resource(ResourceType type);
	~Resource();
};