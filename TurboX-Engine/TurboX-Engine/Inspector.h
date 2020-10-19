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
};

#endif // !__INSPECTOR_H_
