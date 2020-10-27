#ifndef __HIERARCHY_H_
#define __HIERARCHY_H_

#include "WindowConfig.h"
#include <vector>

using namespace std;

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

	void SelectSingle(GameObject* gameObject);
	void UnSelectSingle(GameObject* gameObject);
	void DeselectAll();

public:
	std::vector<GameObject*> selectedGameObjects;
};

#endif // !__HIERARCHY_H_
