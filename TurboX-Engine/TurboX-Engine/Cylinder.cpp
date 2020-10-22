#include "Cylinder.h"

Cylinder::Cylinder(float radius, float height, uint sides)
{
}

Cylinder::~Cylinder()
{
}

void Cylinder::Draw()
{
	//Cylinder formulas:
	//http://www.songho.ca/opengl/gl_cylinder.html

	float sectorStep = 2 * PI / sides;
	float sectorAngle;  // radian

	std::vector<float> unitCircleVertices;
	for (int i = 0; i <= sides; ++i)
	{
		sectorAngle = i * sectorStep;
		unitCircleVertices.push_back(cos(sectorAngle)); // x
		unitCircleVertices.push_back(sin(sectorAngle)); // y
		unitCircleVertices.push_back(0);                // z
	}

	std::vector<float>().swap(cylinder_vertices);
	std::vector<float>().swap(cylinder_normals);
	std::vector<float>().swap(cylinder_texcoords);

	// get unit circle vectors on XY-plane
	std::vector<float> unitVertices = unitCircleVertices;

	// put side vertices to arrays
	for (int i = 0; i < 2; ++i)
	{
		float h = -height / 2.0f + i * height;           // z value; -h/2 to h/2
		float t = 1.0f - i;                              // vertical tex coord; 1 to 0

		for (int j = 0, k = 0; j <= sides; ++j, k += 3)
		{
			float ux = unitVertices[k];
			float uy = unitVertices[k + 1];
			float uz = unitVertices[k + 2];
			// position vector
			cylinder_vertices.push_back(ux * radius);             // vx
			cylinder_vertices.push_back(uy * radius);             // vy
			cylinder_vertices.push_back(h);                       // vz

			// normal vector
			cylinder_normals.push_back(ux);                       // nx
			cylinder_normals.push_back(uy);                       // ny
			cylinder_normals.push_back(uz);                       // nz

			// texture coordinate
			cylinder_texcoords.push_back((float)j / sides);       // s
			cylinder_texcoords.push_back(t);                      // t
		}
	}

	// the starting index for the base/top surface
	//NOTE: it is used for generating indices later
	int baseCenterIndex = (int)cylinder_vertices.size() / 3;
	int topCenterIndex = baseCenterIndex + sides + 1; // include center vertex

	// put base and top vertices to arrays
	for (int i = 0; i < 2; ++i)
	{
		float h = -height / 2.0f + i * height;           // z value; -h/2 to h/2
		float nz = -1 + i * 2;                           // z value of normal; -1 to 1

		// center point
		cylinder_vertices.push_back(0);     cylinder_vertices.push_back(0);     cylinder_vertices.push_back(h);
		cylinder_normals.push_back(0);      cylinder_normals.push_back(0);      cylinder_normals.push_back(nz);
		cylinder_texcoords.push_back(0.5f); cylinder_texcoords.push_back(0.5f);

		for (int j = 0, k = 0; j < sides; ++j, k += 3)
		{
			float ux = unitVertices[k];
			float uy = unitVertices[k + 1];
			// position vector
			cylinder_vertices.push_back(ux * radius);             // vx
			cylinder_vertices.push_back(uy * radius);             // vy
			cylinder_vertices.push_back(h);                       // vz

			// normal vector
			cylinder_normals.push_back(0);                        // nx
			cylinder_normals.push_back(0);                        // ny
			cylinder_normals.push_back(nz);                       // nz

			// texture coordinate
			cylinder_texcoords.push_back(-ux * 0.5f + 0.5f);      // s
			cylinder_texcoords.push_back(-uy * 0.5f + 0.5f);      // t
		}
	}

	std::vector<int> indices;
	int k1 = 0;                         // 1st vertex index at base
	int k2 = sides + 1;           // 1st vertex index at top

	// indices for the side surface
	for (int i = 0; i < sides; ++i, ++k1, ++k2)
	{
		// 2 triangles per sector
		// k1 => k1+1 => k2
		cylinder_indices.push_back(k1);
		cylinder_indices.push_back(k1 + 1);
		cylinder_indices.push_back(k2);

		// k2 => k1+1 => k2+1
		cylinder_indices.push_back(k2);
		cylinder_indices.push_back(k1 + 1);
		cylinder_indices.push_back(k2 + 1);
	}

	// indices for the base surface
	//NOTE: baseCenterIndex and topCenterIndices are pre-computed during vertex generation
	//      please see the previous code snippet
	for (int i = 0, k = baseCenterIndex + 1; i < sides; ++i, ++k)
	{
		if (i < sides - 1)
		{
			cylinder_indices.push_back(baseCenterIndex);
			cylinder_indices.push_back(k + 1);
			cylinder_indices.push_back(k);
		}
		else // last triangle
		{
			cylinder_indices.push_back(baseCenterIndex);
			cylinder_indices.push_back(baseCenterIndex + 1);
			cylinder_indices.push_back(k);
		}
	}

	// indices for the top surface
	for (int i = 0, k = topCenterIndex + 1; i < sides; ++i, ++k)
	{
		if (i < sides - 1)
		{
			cylinder_indices.push_back(topCenterIndex);
			cylinder_indices.push_back(k);
			cylinder_indices.push_back(k + 1);
		}
		else // last triangle
		{
			cylinder_indices.push_back(topCenterIndex);
			cylinder_indices.push_back(k);
			cylinder_indices.push_back(topCenterIndex + 1);
		}
	}

	glRotatef(90, 1, 0, 0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &cylinder_vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &cylinder_normals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &cylinder_texcoords[0]);
	glDrawElements(GL_TRIANGLES, cylinder_indices.size(), GL_UNSIGNED_SHORT, &cylinder_indices[0]);
}