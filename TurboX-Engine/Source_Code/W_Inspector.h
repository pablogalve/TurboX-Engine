#ifndef __INSPECTOR_H_
#define __INSPECTOR_H_

#include "WindowConfig.h"

class C_Transform;
class C_Mesh;
class C_Material;
class C_Camera;
class C_ParticleSystem;
class C_Billboard;

class W_Inspector : WindowConfig
{
public:
	W_Inspector();
	~W_Inspector();

	void Draw() override;

	void SetShowWindow() override;
	bool GetShowWindow() override { return showWindow; };
private:
	//Draw info in the inspector
	void DrawTransform(C_Transform* transform);
	void DrawMesh(C_Mesh* mesh);
	void DrawMaterial(C_Material* material);
	void DrawCamera(C_Camera* camera);
	void DrawParticleSystem(C_ParticleSystem* particle_system);
	void DrawBillboard(C_Billboard* billboard);

public:
	char nameBuffer[256];
	bool active;
};

#endif // !__INSPECTOR_H_
