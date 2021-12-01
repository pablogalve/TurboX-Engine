#ifndef __HIERARCHY_H_
#define __HIERARCHY_H_

#include "WindowConfig.h"
#include "ModuleScene.h"
#include "Application.h"
#include <vector>

class Application;
class GameObject;

class W_Hierarchy : WindowConfig
{
public:
	W_Hierarchy();
	~W_Hierarchy();

	void Draw() override;
	void DrawGameObject(GameObject* gameObject, ImGuiTreeNodeFlags default_flags, GameObject* root);

	void SetShowWindow() override;
	bool GetShowWindow() override;

public:
	std::vector<GameObject*> selectedGameObjects;
	bool active;
};

#endif // !__HIERARCHY_H_
