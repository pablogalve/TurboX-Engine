#ifndef __HIERARCHY_H_
#define __HIERARCHY_H_

#include "WindowConfig.h"

class Hierarchy : WindowConfig
{
public:
	Hierarchy();
	~Hierarchy();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };
};

#endif // !__HIERARCHY_H_
