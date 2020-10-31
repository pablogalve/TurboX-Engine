#include "Mesh_Cube.h"
#include "Application.h"
#include "ModuleScene.h"

Mesh_Cube::Mesh_Cube()
{
	
}

Mesh_Cube::~Mesh_Cube()
{
}

void Mesh_Cube::LoadTexture(const char* file_name)
{
	/*GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	
	for (int i = 0; i < CHECKERS_HEIGHT; i++)
	{
		for (int j = 0; j < CHECKERS_WIDTH; j++)
		{
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkerImage[i][j][0] = (GLubyte)c;
			checkerImage[i][j][1] = (GLubyte)c;
			checkerImage[i][j][2] = (GLubyte)c;
			checkerImage[i][j][3] = (GLubyte)255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);

	ILenum Error;
	Error = ilGetError();

	ilGenImages(1, &ImageName);
	ilBindImage(ImageName);
	ilLoadImage(file_name);
	TextureID = ilutGLBindTexImage();
	ilDeleteImages(1, &ImageName);*/
	
}

void Mesh_Cube::Draw()
{
	/*//cube in direct mode
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glBegin(GL_TRIANGLES);

	glTexCoord2f(1.0f, 1.0f);glVertex3f(0.f, 2.f, 0.f);
	glTexCoord2f(0.0f, 1.0f);glVertex3f(0.f, 0.f, 0.f);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(0.f, 0.f, 2.f);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(0.f, 0.f, 2.f);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(0.f, 2.f, 2.f);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(0.f, 2.f, 0.f);
	
	glTexCoord2f(0.0f, 0.0f);glVertex3f(2.f, 2.f, 0.f);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(2.f, 0.f, 2.f);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(2.f, 0.f, 0.f);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(2.f, 0.f, 2.f);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(2.f, 2.f, 0.f);
	glTexCoord2f(0.0f, 1.0f);glVertex3f(2.f, 2.f, 2.f);
	
	glTexCoord2f(1.0f, 1.0f);glVertex3f(0.f, 2.f, 0.f);
	glTexCoord2f(0.0f, 1.0f);glVertex3f(2.f, 2.f, 0.f);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(2.f, 0.f, 0.f);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(0.f, 2.f, 0.f);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(2.f, 0.f, 0.f);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(0.f, 0.f, 0.f);

	glTexCoord2f(0.0f, 1.0f);glVertex3f(0.f, 2.f, 2.f);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(2.f, 0.f, 2.f);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(2.f, 2.f, 2.f);
	glTexCoord2f(0.0f, 1.0f);glVertex3f(0.f, 2.f, 2.f);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(0.f, 0.f, 2.f);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(2.f, 0.f, 2.f);

	glTexCoord2f(0.0f, 0.0f);glVertex3f(0.f, 2.f, 2.f);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(2.f, 2.f, 2.f);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(2.f, 2.f, 0.f);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(0.f, 2.f, 2.f);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(2.f, 2.f, 0.f);
	glTexCoord2f(0.0f, 1.0f);glVertex3f(0.f, 2.f, 0.f);
	
	glTexCoord2f(0.0f, 1.0f);glVertex3f(0.f, 0.f, 2.f);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(2.f, 0.f, 0.f);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(2.f, 0.f, 2.f);
	glTexCoord2f(0.0f, 1.0f);glVertex3f(0.f, 0.f, 2.f);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(0.f, 0.f, 0.f);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(2.f, 0.f, 0.f);
	
	glEnd();
	glLineWidth(1.0f);
	glBindTexture(GL_TEXTURE_2D, 0);*/
}

void Mesh_Cube::DrawCubeWithArrays()
{
	//Draw a cube with Vertex Arrays and glDrawArrays()
	GLfloat vertices[] =
	{
		0.f, 2.f, 0.f,
		0.f, 0.f, 0.f,
		0.f, 0.f, 2.f,
		0.f, 0.f, 2.f,
		0.f, 2.f, 2.f,
		0.f, 2.f, 0.f,

		2.f, 2.f, 0.f,
		2.f, 0.f, 2.f,
		2.f, 0.f, 0.f,
		2.f, 0.f, 2.f,
		2.f, 2.f, 0.f,
		2.f, 2.f, 2.f,

		0.f, 2.f, 0.f,
		2.f, 2.f, 0.f,
		2.f, 0.f, 0.f,
		0.f, 2.f, 0.f,
		2.f, 0.f, 0.f,
		0.f, 0.f, 0.f,

		0.f, 2.f, 2.f,
		2.f, 0.f, 2.f,
		2.f, 2.f, 2.f,
		0.f, 2.f, 2.f,
		0.f, 0.f, 2.f,
		2.f, 0.f, 2.f,

		0.f, 2.f, 2.f,
		2.f, 2.f, 2.f,
		2.f, 2.f, 0.f,
		0.f, 2.f, 2.f,
		2.f, 2.f, 0.f,
		0.f, 2.f, 0.f,

		0.f, 0.f, 2.f,
		2.f, 0.f, 0.f,
		2.f, 0.f, 2.f,
		0.f, 0.f, 2.f,
		0.f, 0.f, 0.f,
		2.f, 0.f, 0.f
	};

	uint my_id = 0;
	glGenBuffers(1, (GLuint*)&(my_id));
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 108, vertices, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Mesh_Cube::DrawCubeWithIndices()
{
	GLfloat vertices[] = { 2.f, 2.f, 0.f,
		0.f, 2.f, 0.f,
		0.f, 0.f, 0.f,
		2.f, 0.f, 0.f,
		2.f, 0.f, -2.f,
		2.f, 2.f, -2.f,
		0.f, 2.f, -2.f,
		0.f, 0.f, -2.f, };          // 8 of vertex coords

	GLubyte indices[] = { 0,1,2, 2,3,0,   // 36 of indices
						 0,3,4, 4,5,0,
						 0,5,6, 6,1,0,
						 1,6,7, 7,2,1,
						 7,4,3, 3,2,7,
						 4,7,6, 6,5,4 };

	// activate and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	// draw a cube
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
}