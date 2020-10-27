#include "Globals.h"
#include "Application.h"
#include "ModuleImporter.h"
#include "ModuleConsole.h"

ModuleImporter::ModuleImporter(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Importer";
}

// Destructor
ModuleImporter::~ModuleImporter()
{}

// Called before render is available
bool ModuleImporter::Init(JSON_Object* obj)
{

	bool ret = true;
	json_object_clear(obj);
	return ret;
}

// Called before quitting
bool ModuleImporter::CleanUp()
{
	delete ourMesh;

	return true;
}

void ModuleImporter::LoadFBX(char* file_path)
{
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	
	//ourMesh = new C_Mesh(Component::Type::Mesh, this);

	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* meshIterator = scene->mMeshes[i];
			
			// copy vertices
			ourMesh->num_vertex = meshIterator->mNumVertices;
			ourMesh->vertex = new float[ourMesh->num_vertex * 3];
			memcpy(ourMesh->vertex, meshIterator->mVertices, sizeof(float) * ourMesh->num_vertex * 3);
			MY_LOG("New mesh with %d vertices", ourMesh->num_vertex);
			App->console->AddLog("New mesh with %d vertices", ourMesh->num_vertex);

			// copy faces
			if (meshIterator->HasFaces())
			{
				ourMesh->num_index = meshIterator->mNumFaces * 3;
				ourMesh->index = new uint[ourMesh->num_index]; // assume each face is a triangle
				for (uint i = 0; i < meshIterator->mNumFaces; ++i)
				{
					if (meshIterator->mFaces[i].mNumIndices != 3)
					{
						MY_LOG("WARNING, geometry face with != 3 indices!");
						App->console->AddLog("WARNING, geometry face with != 3 indices!");
					}
					else 
					{ 
						memcpy(&ourMesh->index[i * 3], meshIterator->mFaces[i].mIndices, 3 * sizeof(uint));
					}
				}
			}

			if (meshIterator->HasNormals())
			{
				ourMesh->num_normals = meshIterator->mNumVertices;
				ourMesh->normals = new float[ourMesh->num_normals * 3];
				memcpy(ourMesh->normals, meshIterator->mNormals, sizeof(float) * ourMesh->num_normals * 3);
			}

			if (meshIterator->HasTextureCoords(0))
			{
				ourMesh->num_texcoords = meshIterator->mNumVertices;
				ourMesh->texcoords = new float[ourMesh->num_texcoords * 2];
				for (unsigned int i = 0, v = 0; i < ourMesh->num_texcoords; i++, v += 2)
				{
					ourMesh->texcoords[v] = meshIterator->mTextureCoords[0][i].x;
					ourMesh->texcoords[v + 1] = meshIterator->mTextureCoords[0][i].y;
				}
			}
		}

		aiReleaseImport(scene);
	}
	else {
		MY_LOG("Error loading scene % s", file_path);
		App->console->AddLog("Error loading scene % s", file_path);
	}

	ourMesh->SetMeshBuffer();
}