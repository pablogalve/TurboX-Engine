#ifndef __TOOLBAR_H_
#define __TOOLBAR_H_

#include "WindowConfig.h"

class W_Toolbar : WindowConfig
{
public:
	W_Toolbar();
	~W_Toolbar();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };
};

#endif // !__TOOLBAR_H_
