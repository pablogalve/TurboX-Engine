#ifndef __EXPLORER_H_
#define __EXPLORER_H_

#include "WindowConfig.h"
#include "Application.h"
#include "ModuleFileSystem.h"
#include "ModuleResources.h"
#include <vector>

class W_Explorer : WindowConfig
{
public:
	W_Explorer();
	~W_Explorer();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override;

private:
	std::string currDir;
};

#endif // !__EXPLORER_H_
