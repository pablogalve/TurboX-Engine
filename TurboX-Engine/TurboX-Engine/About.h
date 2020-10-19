#ifndef __ABOUT_H_
#define __ABOUT_H_

#include "WindowConfig.h"

class About : WindowConfig
{
public:
	About();
	~About();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };
};

#endif // !__ABOUT_H_
