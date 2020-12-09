#ifndef __EXPLORER_H_
#define __EXPLORER_H_

#include "WindowConfig.h"
#include <vector>

class W_Explorer : WindowConfig
{
public:
	W_Explorer();
	~W_Explorer();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };

private:
	std::string currDir = ASSETS_PATH;
};

#endif // !__EXPLORER_H_
