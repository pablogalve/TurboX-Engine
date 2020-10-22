#include "Sphere.h"

Sphere::Sphere(float _radius, unsigned int _rings, unsigned int _sectors)
{
}

Sphere::~Sphere()
{
}

void Sphere::Draw()
{
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;
	std::vector<GLushort> indices;

	float const R = 1. / (float)(_rings - 1);
	float const S = 1. / (float)(_sectors - 1);
	int r, s;

	vertices.resize(_rings * _sectors * 3);
	normals.resize(_rings * _sectors * 3);
	texcoords.resize(_rings * _sectors * 2);
	std::vector<GLfloat>::iterator v = vertices.begin();
	std::vector<GLfloat>::iterator n = normals.begin();
	std::vector<GLfloat>::iterator t = texcoords.begin();

	for (r = 0; r < _rings; r++) for (s = 0; s < _sectors; s++) {
		float const y = sin(-M_PI_2 + M_PI * r * R);
		float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
		float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

		*t++ = s * S;
		*t++ = r * R;

		*v++ = x * _radius;
		*v++ = y * _radius;
		*v++ = z * _radius;

		*n++ = x;
		*n++ = y;
		*n++ = z;
	}

	indices.resize(_rings * _sectors * 4);
	std::vector<GLushort>::iterator i = indices.begin();
	for (r = 0; r < _rings - 1; r++) for (s = 0; s < _sectors - 1; s++) {
		*i++ = r * _sectors + s;
		*i++ = r * _sectors + (s + 1);
		*i++ = (r + 1) * _sectors + (s + 1);
		*i++ = (r + 1) * _sectors + s;
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(0, 0, 0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &normals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
	glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
	glPopMatrix();
}