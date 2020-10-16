#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"

ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	_cull_face = false;
	_lighting = false;
	_wireframe = false;
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

bool ModuleRenderer3D::Start()
{

	bool ret = true;

	return ret;
}

// Called before render is available
bool ModuleRenderer3D::Init(JSON_Object* obj)
{
	App->console->AddLog("Creating 3D Renderer context");
	//LOG("Creating 3D Renderer context");
	bool ret = true;

	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if (context == NULL)
	{
		App->console->AddLog("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		//LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (ret == true)
	{
		//Use Vsync
		if (VSYNC && SDL_GL_SetSwapInterval(1) < 0){
			App->console->AddLog("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
		//LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
		}

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			App->console->AddLog("Error initializing OpenGL! %s\n", __glewErrorStringREGAL(error));
			//LOG("Error initializing OpenGL! %s\n", __glewErrorStringREGAL(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			App->console->AddLog("Error initializing OpenGL! %s\n", __glewErrorStringREGAL(error));
			//LOG("Error initializing OpenGL! %s\n", __glewErrorStringREGAL(error));
			ret = false;
		}

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);

		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			App->console->AddLog("Error initializing OpenGL! %s\n", __glewErrorStringREGAL(error));
			//LOG("Error initializing OpenGL! %s\n", __glewErrorStringREGAL(error));
			ret = false;
		}

		GLfloat LightModelAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);

		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();

		GLfloat MaterialAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);

		lights[0].Active(true);
		
		
	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	glewInit();
	json_object_clear(obj);
	return ret;
}
// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for (uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{

	//DrawCubeWithDirectMode();
	//DrawCubeWithArrays();
	//DrawCubeWithIndices();
	//DrawPyramid();
	//DrawSphere(1, 12, 24);
	//DrawCylinder(1, 2, 10);
	DrawCone(1,2,10);

	App->gui->Draw();
	
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	App->console->AddLog("Destroying 3D Renderer");
	//LOG("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context);

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ModuleRenderer3D::GL_Enable(unsigned int flag, bool active)
{
	if (active)
		glEnable(flag);
	else
		glDisable(flag);
}

void ModuleRenderer3D::SetWireframeMode(bool active) 
{
	if (active)glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ModuleRenderer3D::DrawCubeWithDirectMode()
{
	//cube in direct mode
	glBegin(GL_TRIANGLES);

	glVertex3f(0.f, 2.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 2.f);
	glVertex3f(0.f, 0.f, 2.f);
	glVertex3f(0.f, 2.f, 2.f);
	glVertex3f(0.f, 2.f, 0.f);

	glVertex3f(2.f, 2.f, 0.f);
	glVertex3f(2.f, 0.f, 2.f);
	glVertex3f(2.f, 0.f, 0.f);
	glVertex3f(2.f, 0.f, 2.f);
	glVertex3f(2.f, 2.f, 0.f);
	glVertex3f(2.f, 2.f, 2.f);

	glVertex3f(0.f, 2.f, 0.f);
	glVertex3f(2.f, 2.f, 0.f);
	glVertex3f(2.f, 0.f, 0.f);
	glVertex3f(0.f, 2.f, 0.f);
	glVertex3f(2.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);

	glVertex3f(0.f, 2.f, 2.f);
	glVertex3f(2.f, 0.f, 2.f);
	glVertex3f(2.f, 2.f, 2.f);
	glVertex3f(0.f, 2.f, 2.f);
	glVertex3f(0.f, 0.f, 2.f);
	glVertex3f(2.f, 0.f, 2.f);

	glVertex3f(0.f, 2.f, 2.f);
	glVertex3f(2.f, 2.f, 2.f);
	glVertex3f(2.f, 2.f, 0.f);
	glVertex3f(0.f, 2.f, 2.f);
	glVertex3f(2.f, 2.f, 0.f);
	glVertex3f(0.f, 2.f, 0.f);

	glVertex3f(0.f, 0.f, 2.f);
	glVertex3f(2.f, 0.f, 0.f);
	glVertex3f(2.f, 0.f, 2.f);
	glVertex3f(0.f, 0.f, 2.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(2.f, 0.f, 0.f);

	glEnd();
	glLineWidth(1.0f);
}

void ModuleRenderer3D::DrawCubeWithArrays()
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

void ModuleRenderer3D::DrawCubeWithIndices()
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

void ModuleRenderer3D::DrawPyramid()
{
	GLfloat vertices[] = {
		1.f, 2.f, 1.f,
		0.f, 0.f, 0.f,
		2.f, 0.f, 0.f,
		2.f, 0.f, 2.f,
		0.f, 0.f, 2.f, };          // 5 of vertex coords

	GLubyte indices[] = { 0,1,2, 2,3,0,   // 24 of indices
						 0,3,4, 0,4,1,
						 1,2,3, 3,4,1, };

	// activate and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	// draw a pyramid
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, indices);

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
}

void ModuleRenderer3D::DrawSphere(float _radius, unsigned int _rings, unsigned int _sectors)
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
	for (r = 0; r < _rings-1; r++) for (s = 0; s < _sectors-1; s++) {
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

void ModuleRenderer3D::DrawCylinder(float radius, float height, uint sides)
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

void ModuleRenderer3D::DrawCone(float radius, float height, uint sides)
{
	
}
