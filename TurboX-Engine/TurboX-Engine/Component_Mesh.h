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

class C_Mesh : public Component {
public:
	C_Mesh(Component::Type type, GameObject* owner);
	~C_Mesh();

	void Draw();
	void SetMeshBuffer();;

	Component::Type GetComponentType() override;

	void DrawVertexNormals();

public:
	
	uint id_index = -1;
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = -1;
	uint num_vertex = 0;
	float3* vertex = nullptr;

	uint id_normals = -1;
	uint num_normals = 0;
	float3* normals = nullptr;

	uint num_textureCoords = 0;
	float2* texturesCoords = nullptr;

	C_Material* material = nullptr;
	C_Transform* transform = nullptr;

	bool vertex_normals_active;

};
#endif // !__COMPONENT_LIGHT_H_
