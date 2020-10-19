#ifndef __EXPLORER_H_
#define __EXPLORER_H_

#include "WindowConfig.h"

class Explorer : WindowConfig
{
public:
	Explorer();
	~Explorer();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };
};

#endif // !__EXPLORER_H_
