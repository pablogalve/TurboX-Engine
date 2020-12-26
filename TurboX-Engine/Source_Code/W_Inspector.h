#ifndef __INSPECTOR_H_
#define __INSPECTOR_H_

#include "WindowConfig.h"

class W_Inspector : WindowConfig
{
public:
	W_Inspector();
	~W_Inspector();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };

public:
	char nameBuffer[256];
	bool active;
};

#endif // !__INSPECTOR_H_
