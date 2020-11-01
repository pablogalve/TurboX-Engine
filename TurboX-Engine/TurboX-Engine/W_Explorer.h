#ifndef __EXPLORER_H_
#define __EXPLORER_H_

#include "WindowConfig.h"

class W_Explorer : WindowConfig
{
public:
	W_Explorer();
	~W_Explorer();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };
};

#endif // !__EXPLORER_H_
