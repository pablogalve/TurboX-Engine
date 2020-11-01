#ifndef __SCENEWINDOW_H_
#define __SCENEWINDOW_H_

#include "WindowConfig.h"
#include "glew\glew.h"

#pragma comment (lib, "Libraries/glew/glew32.lib")    /* link OpenGL Utility lib     */

class W_SceneWindow : WindowConfig
{
public:
	W_SceneWindow();
	~W_SceneWindow();

	void Draw(GLuint texture);

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };
};

#endif // !__SCENEWINDOW_H_