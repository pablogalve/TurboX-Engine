#ifndef __THEME_H_
#define __THEME_H_

#include "WindowConfig.h"

class Theme : WindowConfig
{
public:
	Theme();
	~Theme();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };

private:
	enum class Themes {
		DARK,
		LIGHT,
		CLASSIC
	};

	Themes current_theme;
};

#endif // !__THEME_H_
