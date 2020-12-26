#ifndef __ABOUT_H_
#define __ABOUT_H_

#include "WindowConfig.h"

class W_About : WindowConfig
{
public:
	W_About();
	~W_About();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };
};

#endif // !__ABOUT_H_
