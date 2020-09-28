
#pragma once
#include "glmath.h"
#include "Color.h"
#include "PhysBody3D.h"

enum PrimitiveTypes
{
	Primitive_Point,
	Primitive_Line,
	Primitive_Plane,
	Primitive_Cube,
	Primitive_Sphere,
	Primitive_Cylinder
};

class Primitive
{
public:
	Primitive();

	void Update();
	virtual void	Render() const;
	void			SetPos(float x, float y, float z);
	void			SetRotation(float angle, const vec3 &u);
	void			Scale(float x, float y, float z);
	PrimitiveTypes	GetType() const;


	Color color;
	mat4x4 transform;
	bool axis,wire;
	PhysBody3D body;

protected:
	virtual void InnerRender() const;
	PrimitiveTypes type;
};

// ============================================
class Cube : public Primitive
{
public :
	Cube(const vec3& size = vec3(1.f,1.f,1.f), float mass = 1.f);

	vec3 GetSize() const;
protected:
	void InnerRender() const;
private:
	vec3 size;
};

// ============================================
class Sphere : public Primitive
{
public:
	Sphere(float radius = 1.f, float mass = 1.f);

	float GetRadius() const;
protected:
	void InnerRender() const;
private:
	float radius;
};

// ============================================
class Cylinder : public Primitive
{
public:
	Cylinder(float radius = 1.f, float height = 2.f, float mass = 1.f);

	float GetRadius() const;
	float GetHeight() const;
protected:
	void InnerRender() const;
private:
	float radius;
	float height;
};

// ============================================
class Line : public Primitive
{
public:
	Line();
	Line(const vec3& A, const vec3& B);

	vec3 GetOrigin() const;
	vec3 GetDestination() const;

protected:
	void InnerRender() const;
public:
	vec3 origin;
	vec3 destination;
};

// ============================================
class Plane : public Primitive
{
public:
	Plane(const vec3& normal = vec3(0,1,0));

	vec3 GetNormal() const;
protected:
	void InnerRender() const;
private:
	vec3 normal;
};