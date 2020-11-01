#ifndef __RESOURCES_H_
#define __RESOURCES_H_

#include "WindowConfig.h"

class W_Resources : WindowConfig
{
public:
	W_Resources();
	~W_Resources();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };
};

#endif // !__RESOURCES_H_
