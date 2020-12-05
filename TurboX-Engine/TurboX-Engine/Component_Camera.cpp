#include "Application.h"
#include "ModuleScene.h"
#include "GameObject.h"
#include "Component_Camera.h"
#include "Component_Transformation.h"


C_Camera::C_Camera(Component::Type type, GameObject* owner) :Component(type, owner)
{
	frustum.type = math::FrustumType::PerspectiveFrustum;

	frustum.pos = { -10.0f,5.0f,-9.0f };
	frustum.front = { 0.0f,0.0f,-1.0f };
	frustum.up = { 0.0f,1.0f,0.0f };

	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 1000.0f;

	frustum.verticalFov = DEGTORAD * 90.0f;
	setAspectRatio(16.0f / 9.0f);

	RecalculateBB();	
}

C_Camera::~C_Camera()
{
}

Component::Type C_Camera::GetComponentType()
{
	return Component::Type::Camera;
}

float* C_Camera::getViewMatrix()
{
	static float4x4 matrix;
	matrix = frustum.ViewMatrix();
	matrix.Transpose();

	return (float*)matrix.v;
}

float* C_Camera::getProjectionMatrix()
{
	static float4x4 matrix;
	matrix = frustum.ProjectionMatrix();
	matrix.Transpose();

	return (float*)matrix.v;
}

void C_Camera::setAspectRatio(float aspectRatio)
{
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspectRatio);
}

void C_Camera::DrawFrustum()
{
	float3 corners[8];
	frustum.GetCornerPoints(corners);

	glLineWidth(2.0f);
	//glColor3f(color.x, color.y, color.z);

	glBegin(GL_LINES);

	glVertex3f(corners[0].x, corners[0].y, corners[0].z);
	glVertex3f(corners[1].x, corners[1].y, corners[1].z);

	glVertex3f(corners[0].x, corners[0].y, corners[0].z);
	glVertex3f(corners[2].x, corners[2].y, corners[2].z);

	glVertex3f(corners[0].x, corners[0].y, corners[0].z);
	glVertex3f(corners[4].x, corners[4].y, corners[4].z);

	glVertex3f(corners[1].x, corners[1].y, corners[1].z);
	glVertex3f(corners[3].x, corners[3].y, corners[3].z);

	glVertex3f(corners[1].x, corners[1].y, corners[1].z);
	glVertex3f(corners[5].x, corners[5].y, corners[5].z);

	glVertex3f(corners[2].x, corners[2].y, corners[2].z);
	glVertex3f(corners[3].x, corners[3].y, corners[3].z);

	glVertex3f(corners[2].x, corners[2].y, corners[2].z);
	glVertex3f(corners[6].x, corners[6].y, corners[6].z);

	glVertex3f(corners[3].x, corners[3].y, corners[3].z);
	glVertex3f(corners[7].x, corners[7].y, corners[7].z);

	glVertex3f(corners[4].x, corners[4].y, corners[4].z);
	glVertex3f(corners[5].x, corners[5].y, corners[5].z);

	glVertex3f(corners[4].x, corners[4].y, corners[4].z);
	glVertex3f(corners[6].x, corners[6].y, corners[6].z);

	glVertex3f(corners[5].x, corners[5].y, corners[5].z);
	glVertex3f(corners[7].x, corners[7].y, corners[7].z);

	glVertex3f(corners[6].x, corners[6].y, corners[6].z);
	glVertex3f(corners[7].x, corners[7].y, corners[7].z);

	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(1.0f);
}

bool C_Camera::ContainsAABB(const AABB& boundingBox)
{
	Plane planes[6];
	float3 corners[8];
	int counter = 0;

	boundingBox.GetCornerPoints(corners);
	frustum.GetPlanes(planes);

	for (int i = 0; i < 6; i++)
	{
		//This number checks if the bb is outside of a plane
		int aux_count = counter;

		for (int j = 0; j < 8; j++)
		{
			if (!planes[i].IsOnPositiveSide(corners[j]))
			{
				counter++;
				break;
			}
		}
		if (aux_count == counter)
		{
			return false;
		}
	}

	if (counter == 6)
	{
		return true;
	}

	return false;
}

void C_Camera::CameraBB()
{
	glLineWidth(1.5f);
	glColor3f(1, 0.5f, 1);

	glBegin(GL_LINES);

	glVertex3f(cameraBB.CornerPoint(0).x, cameraBB.CornerPoint(0).y, cameraBB.CornerPoint(0).z);
	glVertex3f(cameraBB.CornerPoint(1).x, cameraBB.CornerPoint(1).y, cameraBB.CornerPoint(1).z);

	glVertex3f(cameraBB.CornerPoint(0).x, cameraBB.CornerPoint(0).y, cameraBB.CornerPoint(0).z);
	glVertex3f(cameraBB.CornerPoint(2).x, cameraBB.CornerPoint(2).y, cameraBB.CornerPoint(2).z);

	glVertex3f(cameraBB.CornerPoint(0).x, cameraBB.CornerPoint(0).y, cameraBB.CornerPoint(0).z);
	glVertex3f(cameraBB.CornerPoint(4).x, cameraBB.CornerPoint(4).y, cameraBB.CornerPoint(4).z);

	glVertex3f(cameraBB.CornerPoint(3).x, cameraBB.CornerPoint(3).y, cameraBB.CornerPoint(3).z);
	glVertex3f(cameraBB.CornerPoint(1).x, cameraBB.CornerPoint(1).y, cameraBB.CornerPoint(1).z);

	glVertex3f(cameraBB.CornerPoint(3).x, cameraBB.CornerPoint(3).y, cameraBB.CornerPoint(3).z);
	glVertex3f(cameraBB.CornerPoint(2).x, cameraBB.CornerPoint(2).y, cameraBB.CornerPoint(2).z);

	glVertex3f(cameraBB.CornerPoint(3).x, cameraBB.CornerPoint(3).y, cameraBB.CornerPoint(3).z);
	glVertex3f(cameraBB.CornerPoint(7).x, cameraBB.CornerPoint(7).y, cameraBB.CornerPoint(7).z);

	glVertex3f(cameraBB.CornerPoint(6).x, cameraBB.CornerPoint(6).y, cameraBB.CornerPoint(6).z);
	glVertex3f(cameraBB.CornerPoint(2).x, cameraBB.CornerPoint(2).y, cameraBB.CornerPoint(2).z);

	glVertex3f(cameraBB.CornerPoint(6).x, cameraBB.CornerPoint(6).y, cameraBB.CornerPoint(6).z);
	glVertex3f(cameraBB.CornerPoint(4).x, cameraBB.CornerPoint(4).y, cameraBB.CornerPoint(4).z);

	glVertex3f(cameraBB.CornerPoint(6).x, cameraBB.CornerPoint(6).y, cameraBB.CornerPoint(6).z);
	glVertex3f(cameraBB.CornerPoint(7).x, cameraBB.CornerPoint(7).y, cameraBB.CornerPoint(7).z);

	glVertex3f(cameraBB.CornerPoint(5).x, cameraBB.CornerPoint(5).y, cameraBB.CornerPoint(5).z);
	glVertex3f(cameraBB.CornerPoint(1).x, cameraBB.CornerPoint(1).y, cameraBB.CornerPoint(1).z);

	glVertex3f(cameraBB.CornerPoint(5).x, cameraBB.CornerPoint(5).y, cameraBB.CornerPoint(5).z);
	glVertex3f(cameraBB.CornerPoint(4).x, cameraBB.CornerPoint(4).y, cameraBB.CornerPoint(4).z);

	glVertex3f(cameraBB.CornerPoint(5).x, cameraBB.CornerPoint(5).y, cameraBB.CornerPoint(5).z);
	glVertex3f(cameraBB.CornerPoint(7).x, cameraBB.CornerPoint(7).y, cameraBB.CornerPoint(7).z);

	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(1.0f);
}

void C_Camera::RecalculateBB()
{
	float3 corner[8];
	frustum.GetCornerPoints(corner);

	cameraBB.SetNegativeInfinity();
	cameraBB.Enclose(corner, 8);
}
