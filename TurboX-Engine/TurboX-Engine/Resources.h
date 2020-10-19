#ifndef __RESOURCES_H_
#define __RESOURCES_H_

#include "WindowConfig.h"

class Resources : WindowConfig
{
public:
	Resources();
	~Resources();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };
};

#endif // !__RESOURCES_H_
