#ifndef __SCENEWINDOW_H_
#define __SCENEWINDOW_H_

#include "WindowConfig.h"

class SceneWindow : WindowConfig
{
public:
	SceneWindow();
	~SceneWindow();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };
};

#endif // !__SCENEWINDOW_H_
