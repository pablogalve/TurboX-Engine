#ifndef __HIERARCHY_H_
#define __HIERARCHY_H_

#include "WindowConfig.h"

class Application;
class GameObject;

class Hierarchy : WindowConfig
{
public:
	Hierarchy();
	~Hierarchy();

	void Draw() override;
	void Draw(Application* App);
	void DrawGameObject(GameObject* gameObject, ImGuiTreeNodeFlags default_flags, GameObject* root);

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };
};

#endif // !__HIERARCHY_H_
