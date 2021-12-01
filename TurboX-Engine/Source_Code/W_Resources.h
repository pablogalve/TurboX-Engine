#ifndef __RESOURCES_H_
#define __RESOURCES_H_

#include "WindowConfig.h"
#include <vector>
#include <map>

class Resource;

class W_Resources : WindowConfig
{
public:
	W_Resources();
	~W_Resources();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override;

	void DrawResourcesChilds(std::map<uint, Resource* > resources);
};

#endif // !__RESOURCES_H_
