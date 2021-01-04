#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"
#include "ModuleConsole.h"
#include "ModuleScene.h"
#include "ModuleEditor.h"
#include "W_Hierarchy.h"
#include "GameObject.h"
#include "MathGeoLib/MathGeoLib.h"
#include "ModuleRenderer3D.h"
#include "Component.h"
#include "Component_Camera.h"
#include "Component_Mesh.h"
#include "Component_Transformation.h"
#include "ResourceMesh.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Camera";

	X = { 1.0f,0.0f,0.0f };
	Y = { 0.0f,1.0f,0.0f };
	Z = { 0.0f,0.0f,1.0f };
	Position = { 0.0f, 20.0f, 30.0f };
	Reference = { 0.0f,0.0f,0.0f };
	
	cameraLookingAtSelectedGameObject = false;
	camera = new C_Camera(Component::Type::Camera, nullptr);
	camera->active = false;

}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	MY_LOG("Setting up the camera");
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	MY_LOG("Cleaning camera");

	return true;
}

bool ModuleCamera3D::LoadSettings(Config* data)
{
	cameraSpeed = data->GetFloat("cameraSpeed");
	mouseSensitivity = data->GetFloat("mouseSensitivity");
	wheelSensitivity = data->GetFloat("wheelSensitivity");
	zoomDistance = data->GetFloat("zoomDistance");

	return true;
}

bool ModuleCamera3D::SaveSettings(Config* data) const
{
	data->AddFloat("cameraSpeed", cameraSpeed);
	data->AddFloat("mouseSensitivity", mouseSensitivity);
	data->AddFloat("wheelSensitivity", wheelSensitivity);
	data->AddFloat("zoomDistance", zoomDistance);
	return true;
}

void ModuleCamera3D::OnResize(int width, int height)
{
	float newAR = (float)width / (float)height;
	camera->setAspectRatio(newAR);
	App->renderer3D->changedFOV = true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{
		vec newPos(0, 0, 0);
		float speed = cameraSpeed * dt;
		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			speed *= 2;
		else if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)
			speed /= 2;

		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) newPos.y += speed;
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) newPos.y -= speed;

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos += camera->frustum.front * speed;
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos -= camera->frustum.front * speed;


		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= camera->frustum.WorldRight() * speed;
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += camera->frustum.WorldRight() * speed;

		Position += newPos;
		Reference += newPos;

		Reference = Position - GetMovementFactor();
	}

	// Rotation over object ----------------
	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		camera->frustum.pos = Position = Reference + GetMovementFactor();
	}

	if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT)
	{
		vec newPos(0, 0, 0);
		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		if (dx != 0)
		{
			float DeltaX = (float)dx * mouseSensitivity;

			newPos += X * DeltaX;
		}
		if (dy != 0)
		{
			float DeltaY = (float)dy * mouseSensitivity;

			newPos -= Y * DeltaY;
		}

		Position += newPos;
		Reference += newPos;
	}

	if (App->input->GetMouseZ() != 0)
	{
		vec newPos(0, 0, 0);
		float Sensitivity = wheelSensitivity;
		vec vec_distance = Reference - Position;

		if (vec_distance.Length() < zoomDistance)
		{
			Sensitivity = vec_distance.Length() / zoomDistance;
		}

		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			Sensitivity = 2;

		if (App->input->GetMouseZ() > 0)
		{
			newPos -= Z * Sensitivity;
		}
		else
		{
			newPos += Z * Sensitivity;
		}

		Position += newPos;
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT)
	{
		LookAt({ 0,0,0 });
	}

	camera->frustum.pos = Position;

	Z = -camera->frustum.front;
	Y = camera->frustum.up;
	X = camera->frustum.WorldRight();

	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_LALT) != KEY_REPEAT && (!ImGuizmo::IsEnabled() || !ImGuizmo::IsOver()))
	{
		App->scene->selectGameObject(CheckMousePick());
	}

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec& Position, const vec& Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = (Position - Reference).Normalized();
	X = (vec(0.0f, 1.0f, 0.0f).Cross(Z)).Normalized();
	Y = Z.Cross(X);

	if (!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const vec &Spot)
{
	Reference = Spot;

	//calculate direction to look
	vec dir = Spot - camera->frustum.pos;

	//caluclate the new view matrix
	float3x3 viewMat = float3x3::LookAt(camera->frustum.front, dir.Normalized(), camera->frustum.up, vec(0.0f, 1.0f, 0.0f));

	//set new front and up for the frustum
	camera->frustum.front = viewMat.MulDir(camera->frustum.front).Normalized();
	camera->frustum.up = viewMat.MulDir(camera->frustum.up).Normalized();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec &Movement)
{
	Position += Movement;
	Reference += Movement;

}

void ModuleCamera3D::FitCamera(const AABB& boundingBox)
{
	vec diagonal = boundingBox.Diagonal();
	vec center = boundingBox.CenterPoint();
	Position.z = camera->frustum.pos.z = (center.z + diagonal.Length());
	Position.y = camera->frustum.pos.y = center.y;
	Position.x = camera->frustum.pos.x = center.x;
	LookAt({ center.x,center.y,center.z });
}

vec ModuleCamera3D::GetMovementFactor()
{
	int dx = -App->input->GetMouseXMotion();
	int dy = -App->input->GetMouseYMotion();

	vec newPosition = Position - Reference;

	if (dx != 0)
	{
		float DeltaX = (float)dx * mouseSensitivity;

		Quat rotation = Quat::RotateY(DeltaX);
		camera->frustum.front = rotation.Mul(camera->frustum.front).Normalized();
		camera->frustum.up = rotation.Mul(camera->frustum.up).Normalized();
	}

	if (dy != 0)
	{
		float DeltaY = (float)dy * mouseSensitivity;

		Quat rotation = Quat::RotateAxisAngle(camera->frustum.WorldRight(), DeltaY);

		if (rotation.Mul(camera->frustum.up).Normalized().y > 0.0f)
		{
			camera->frustum.up = rotation.Mul(camera->frustum.up).Normalized();
			camera->frustum.front = rotation.Mul(camera->frustum.front).Normalized();
		}
	}

	return -camera->frustum.front * newPosition.Length();
}


GameObject* ModuleCamera3D::CheckMousePick()
{
	GameObject* ret = nullptr;

	float mouseX = App->input->GetMouseX() - App->editor->sceneX;
	float mouseY = App->input->GetMouseY() - App->editor->sceneY;
	mouseX = (mouseX / (App->editor->sceneW / 2)) - 1;
	mouseY = (mouseY / (App->editor->sceneH / 2)) - 1;
	LineSegment ray = camera->frustum.UnProjectLineSegment(mouseX, -mouseY);
	App->renderer3D->clickA = ray.a;
	App->renderer3D->clickB = ray.b;

	//Fill queue
	std::priority_queue<HitGameObject*, std::vector<HitGameObject*>, OrderCrit> gameObjects;
	fillHitGameObjects(App->scene->root, gameObjects, ray);

	if (gameObjects.size() > 0)
		ret = checkCloserGameObjects(gameObjects, ray);

	return ret;
}

void ModuleCamera3D::fillHitGameObjects(GameObject* current, std::priority_queue<HitGameObject*, std::vector<HitGameObject*>, OrderCrit>& gameObjects, LineSegment ray)
{
	float distance, exitDistance;
	if (ray.Intersects(current->boundingBox, distance, exitDistance))
	{
		HitGameObject* hit = new HitGameObject(current, distance);
		gameObjects.push(hit);
	}

	for (std::vector<GameObject*>::iterator it_c = current->childs.begin(); it_c != current->childs.end(); it_c++)
	{
		fillHitGameObjects((*it_c), gameObjects, ray);
	}
}

GameObject* ModuleCamera3D::checkCloserGameObjects(std::priority_queue<HitGameObject*, std::vector<HitGameObject*>, OrderCrit>& queue, LineSegment ray, float distance)
{
	GameObject* ret = nullptr;

	HitGameObject* curr = queue.top();
	queue.pop();
	float TriDistance = hitsTriangle(curr->GO, ray);
	if (TriDistance != -1 && (TriDistance < distance || distance == -1))
	{
		distance = TriDistance;
		ret = curr->GO;
	}
	if (queue.size() > 0 && (queue.top()->distance < distance || distance == -1))
	{
		GameObject* GO2 = checkCloserGameObjects(queue, ray, distance);
		if (GO2 != nullptr)
			ret = GO2;
	}
	RELEASE(curr);

	return ret;
}

float ModuleCamera3D::hitsTriangle(GameObject* gameObject, LineSegment ray)
{
	float smallestDistance = -1.0f;

	C_Transform* transformation = (C_Transform*)gameObject->GetComponent(Component::Type::Transform);

	if (transformation != nullptr)
		ray.Transform(transformation->globalMatrix.Inverted());

	C_Mesh* mesh = (C_Mesh*)gameObject->GetComponent(Component::Type::Mesh);


	if (mesh != nullptr)
	{
		uint* indices = mesh->GetResourceMesh()->index;
		float3* vertices = mesh->GetResourceMesh()->vertex;

		for (int i = 0; i < mesh->GetResourceMesh()->num_index;)
		{
			math::Triangle tri;
			tri.a = vertices[indices[i]]; ++i;
			tri.b = vertices[indices[i]]; ++i;
			tri.c = vertices[indices[i]]; ++i;

			float distance;
			float3 intPoint;

			bool hit = ray.Intersects(tri, &distance, &intPoint);
			if (distance > 0 && (distance < smallestDistance || smallestDistance == -1.0f))
			{
				smallestDistance = distance;
			}
		}
	}

	return smallestDistance;
}
