#include "Resource.h"
#include "Globals.h"
#include "ModuleResources.h"


Resource::Resource(uint UUID, ResType type) : UUID(UUID), type(type)
{
}

Resource::~Resource()
{
}

void Resource::SetUUID(uint newUUID)
{
	App->resources->ChangeResourceUUID(UUID, newUUID);
	UUID = newUUID; 
}