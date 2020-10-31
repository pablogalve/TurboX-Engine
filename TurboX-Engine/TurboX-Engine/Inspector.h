#ifndef __INSPECTOR_H_
#define __INSPECTOR_H_

#include "WindowConfig.h"

class Inspector : WindowConfig
{
public:
	Inspector();
	~Inspector();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };

public:
	char nameBuffer[256];
};

#endif // !__INSPECTOR_H_
