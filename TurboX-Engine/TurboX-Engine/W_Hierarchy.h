#ifndef __HIERARCHY_H_
#define __HIERARCHY_H_

#include "WindowConfig.h"
#include <vector>

using namespace std;

class Application;
class GameObject;

class W_Hierarchy : WindowConfig
{
public:
	W_Hierarchy();
	~W_Hierarchy();

	void Draw() override;
	void DrawGameObject(GameObject* gameObject, ImGuiTreeNodeFlags default_flags, GameObject* root);
	void OpenPopUpWindow();

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };

	void SelectSingle(GameObject* gameObject);
	void UnSelectSingle(GameObject* gameObject);
	void DeselectAll();

public:
	std::vector<GameObject*> selectedGameObjects;
	bool open_pop_up;
	bool active;

};

#endif // !__HIERARCHY_H_
