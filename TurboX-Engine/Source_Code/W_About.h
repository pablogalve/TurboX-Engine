#ifndef __ABOUT_H_
#define __ABOUT_H_

#include "WindowConfig.h"
#include "Application.h"
#include "Libraries/SDL/include/SDL.h"
#include "Libraries/glew/glew.h"

class W_About : WindowConfig
{
public:
	W_About();
	~W_About();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override;
};

#endif // !__ABOUT_H_
