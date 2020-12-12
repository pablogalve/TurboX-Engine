#ifndef __COMPONENT_MESH_H_
#define __COMPONENT_MESH_H_

#include "Component.h"
#include "Globals.h"
#include "MathGeoLib/Math/MathAll.h"
#include "MathGeoLib/Geometry/AABB.h"
#include "Component_Material.h"
#include "Component_Transformation.h"
#include <array>
#include <vector>

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

class ResourceMesh;

class C_Mesh : public Component {
public:
	C_Mesh(Component::Type type, GameObject* owner);
	~C_Mesh();

	void SetMaterial(C_Material* texture);

	void Draw();
	void SetMeshBuffer();;

	Component::Type GetComponentType() override;

	void DrawVertexNormals();

	bool Save(Config* data) override;
	bool Load(Config* data) override;

	void SetResource(uint resource)override;
	ResourceMesh* GetResourceMesh() const { return resourceMesh; }

public:
	
	ResourceMesh* resourceMesh = nullptr;

	C_Material* material = nullptr;
	C_Transform* transform = nullptr;

	bool vertex_normals_active;
};
#endif // !__COMPONENT_LIGHT_H_
