#include "GameObject.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleRenderer3D.h"
#include "ResourceMesh.h"

GameObject::GameObject()
{	
	active = true;
	ChangeName("Custom Mesh");
	is_selected = false;
	to_delete = false;
	culling = false;
	child_selected = false;
	isStatic = false;

	mesh = nullptr;
	material = nullptr;
	transform = nullptr;
	parent = nullptr;
	camera = nullptr;
	
	UUID = GenerateUUID();	

	CreateComponent(Component::Type::Transform);

	boundingBox = AABB({ 0,0,0 }, { 0,0,0 });
}

GameObject::~GameObject()
{
	
}

Component* GameObject::CreateComponent(Component::Type type)
{
	Component* new_component = nullptr;

	switch (type)
	{
	case Component::Type::None:		
		break;
	case Component::Type::Transform:
		new_component = new C_Transform(Component::Type::Transform, this);
		transform = (C_Transform*)new_component;
		break;
	case Component::Type::Mesh:
		new_component = new C_Mesh(Component::Type::Mesh, this);
		mesh = (C_Mesh*)new_component;
		break;
	case Component::Type::Material:
		new_component = new C_Material(Component::Type::Material, this);
		material = (C_Material*)new_component;
		break;
	case Component::Type::Camera:
		new_component = new C_Camera(Component::Type::Camera, this);
		camera = (C_Camera*)new_component;
		break;
	default:
		break;
	}

	if (new_component)
		components.push_back(new_component);

	return new_component;
}

void GameObject::DestroyComponent(Component::Type type)
{	
	for (int i = 0; i < components.size(); i++)
	{
		if (type == components[i]->GetComponentType())
		{
			components[i]->Disable();
		}
	}
}

Component* GameObject::GetComponent(Component::Type type)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (type == components[i]->GetComponentType())
		{
			return components[i];
		}
	}

	return nullptr;
}

void GameObject::Draw()
{

	if (culling) 
	{
		if (mesh != nullptr)
		{
			glPushMatrix();
			glMultMatrixf((float*)transform->globalMatrix.Transposed().v);
			mesh->Draw();
			glPopMatrix();
		}

	}

	if (camera != nullptr)
	{
		camera->DrawFrustum();

		if (this != nullptr)
		{
			camera->frustum.SetWorldMatrix(transform->globalMatrix.Float3x4Part());
		}
	}

	if (App->renderer3D->ShowBB || is_selected)
	{
		DrawBB(boundingBox, { 0, 0.5f, 1 });
	}
	
	if (transform != nullptr && transform->changed)
	{
		GameObject* bigParent = this;
		while (bigParent->parent != nullptr)
			bigParent = bigParent->parent;
		bigParent->RecalculateBB();
		
		transform->changed = false;
	}

	for (size_t i = 0; i < childs.size(); i++)
	{
		if (childs[i]->active)
			childs[i]->Draw();
	}
}

void GameObject::ChangeName(std::string _name)
{
	name = _name;
}

bool GameObject::Get_IsSelected()
{
	return is_selected;
}

void GameObject::Select()
{
	is_selected = true;
}

void GameObject::Unselect()
{
	is_selected = false;
}

bool GameObject::Save(Config* data)
{
	bool ret = true;

	//Save gameObject info
	data->AddString("Name", name.c_str());
	data->AddUInt("UUID", UUID);
	data->AddUInt("ParentUUID", parentUUID);
	data->AddBool("Active", active);
	data->AddBool("Static", isStatic);

	data->AddArray("Components");

	//Save components info
	for (size_t i = 0; i < components.size(); i++)
	{
		Config componentsData;	
		components[i]->Save(&componentsData);
		data->AddArrayChild(componentsData);		
	}
	
	//Save childs info
	if (!childs.empty())data->AddArray("Childs");
	for (size_t i = 0; i < childs.size(); i++)
	{
		Config childsData;
		childs[i]->Save(&childsData);
		data->AddArrayChild(childsData);
	}

	return ret;
}

bool GameObject::Load(Config* data)
{
	bool ret = true;

	//Load basic information
	UUID = data->GetUInt("UUID");
	parentUUID = data->GetUInt("ParentUUID");
	name = data->GetString("Name", "Unnamed");
	active = data->GetBool("Active", true);
	isStatic = data->GetBool("Static", false);

	GameObject* parent = App->scene->GetGameObjectByUUID(parentUUID);
	if(parent != nullptr)
		SetParent(parent);
	else
		SetParent(App->scene->GetRoot());

	//Load components
	int component_num = data->GetNumElementsInArray("Components");
	if (component_num == -1)MY_LOG("Warning. No components detected for this gameObject");

	for (int i = 0; i < component_num; i++) {
		Config elem = data->GetArray("Components", i);
		Component::Type type = (Component::Type)elem.GetInt("Type");
		if (type != Component::Type::None) {
			Component* comp = CreateComponent(type);
			comp->Load(&elem);
			MY_LOG("Component loaded: %i", type);
		}
		else {
			MY_LOG("Cannot load components correctly. Component type: NOTYPE ");
		}
	}

	//Load childs
	int childs_num = data->GetNumElementsInArray("Childs");
	if (childs_num == -1)MY_LOG("Warning. No components detected for this gameObject");

	for (int i = 0; i < childs_num; i++) {
		Config elem = data->GetArray("Childs", i);
		GameObject* go = new GameObject();
		go->Load(&elem);
	}

	return ret;
}

void GameObject::GetComponents(Component::Type type, std::vector<Component*>& comp)
{
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->GetComponentType() == type) {
			comp.push_back(components[i]);
		}
	}

	for (int i = 0; i < childs.size(); i++) {
		childs[i]->GetComponents(type, comp);
	}
}

C_Material* GameObject::GetComponentMaterial(uint UUID)
{
	std::vector<Component*> materials;

	GetComponents(Component::Type::Material, materials);
	for (int i = 0; i < materials.size(); i++){
		C_Material* it = (C_Material*)materials[i];
		const uint auxuuid = it->GetResourceUUID();
		if (auxuuid == UUID) {
			return it;
		}
		it = nullptr;
	}
	return nullptr;
}

void GameObject::setSelected(bool selected)
{
	this->is_selected = selected;

	if (parent != nullptr)
		parent->setChildSelected(selected);
}

void GameObject::setChildSelected(bool selected)
{
	child_selected = selected;

	if (parent != nullptr)
		parent->setChildSelected(selected);
}

void GameObject::DestroyChildren(GameObject* toRemove)
{
	for (int i = 0; i < childs.size(); i++) {
		if (childs[i] == toRemove) {
			//TODO: Call the gameObject's CleanUp()
			childs.erase(childs.begin() + i);
			return;
		}
	}
}

uint GameObject::GenerateUUID() {
	return LCG().Int();
}

uint GameObject::GetUUID() {
	return UUID;
}

uint GameObject::GetParentUUID() {
	return parent->GetUUID();
}

void GameObject::AddChildren(GameObject* child)
{
	for (int i = 0; i < childs.size(); i++) {
		if (childs[i] == child) {
			return;
		}
	}
	this->childs.push_back(child);
	child->SetParent(this);
}

void GameObject::SetParent(GameObject* _parent)
{
	if (parent != nullptr) {
		if (parent == _parent) {
			return;
		}
		for (std::vector<GameObject*>::iterator iterator = parent->childs.begin(); iterator != parent->childs.end(); iterator++) {
			if (this == (*iterator)) {
				parent->childs.erase(iterator);
				break;
			}
		}
	}
	parent = _parent;
	parent->AddChildren(this);
	parentUUID = parent->GetUUID();
}

void GameObject::RecalculateBB()
{
	if (transform != nullptr)
	{
		boundingBox.SetNegativeInfinity();

		if (childs.size() > 0)
		{
			for (std::vector<GameObject*>::iterator it_c = childs.begin(); it_c != childs.end(); it_c++)
			{
				(*it_c)->RecalculateBB();
				if ((*it_c)->boundingBox.IsFinite())
					boundingBox.Enclose((*it_c)->boundingBox);
			}
		}

		if (mesh != nullptr)
		{
			float3* vertices = mesh->GetResourceMesh()->vertex;
			uint n_vertex = mesh->GetResourceMesh()->num_vertex;
			boundingBox.Enclose(vertices, n_vertex);
		}

		if (childs.size() <= 0)
		{
			boundingBox.TransformAsAABB(transform->globalMatrix);
		}
	}
}

void GameObject::DrawBB(const AABB& BB, vec color) const
{
	glLineWidth(1.5f);
	glColor3f(color.x, color.y, color.z);

	glBegin(GL_LINES);

	glVertex3f(BB.CornerPoint(0).x, BB.CornerPoint(0).y, BB.CornerPoint(0).z);
	glVertex3f(BB.CornerPoint(1).x, BB.CornerPoint(1).y, BB.CornerPoint(1).z);

	glVertex3f(BB.CornerPoint(0).x, BB.CornerPoint(0).y, BB.CornerPoint(0).z);
	glVertex3f(BB.CornerPoint(2).x, BB.CornerPoint(2).y, BB.CornerPoint(2).z);

	glVertex3f(BB.CornerPoint(0).x, BB.CornerPoint(0).y, BB.CornerPoint(0).z);
	glVertex3f(BB.CornerPoint(4).x, BB.CornerPoint(4).y, BB.CornerPoint(4).z);

	glVertex3f(BB.CornerPoint(3).x, BB.CornerPoint(3).y, BB.CornerPoint(3).z);
	glVertex3f(BB.CornerPoint(1).x, BB.CornerPoint(1).y, BB.CornerPoint(1).z);

	glVertex3f(BB.CornerPoint(3).x, BB.CornerPoint(3).y, BB.CornerPoint(3).z);
	glVertex3f(BB.CornerPoint(2).x, BB.CornerPoint(2).y, BB.CornerPoint(2).z);

	glVertex3f(BB.CornerPoint(3).x, BB.CornerPoint(3).y, BB.CornerPoint(3).z);
	glVertex3f(BB.CornerPoint(7).x, BB.CornerPoint(7).y, BB.CornerPoint(7).z);

	glVertex3f(BB.CornerPoint(6).x, BB.CornerPoint(6).y, BB.CornerPoint(6).z);
	glVertex3f(BB.CornerPoint(2).x, BB.CornerPoint(2).y, BB.CornerPoint(2).z);

	glVertex3f(BB.CornerPoint(6).x, BB.CornerPoint(6).y, BB.CornerPoint(6).z);
	glVertex3f(BB.CornerPoint(4).x, BB.CornerPoint(4).y, BB.CornerPoint(4).z);

	glVertex3f(BB.CornerPoint(6).x, BB.CornerPoint(6).y, BB.CornerPoint(6).z);
	glVertex3f(BB.CornerPoint(7).x, BB.CornerPoint(7).y, BB.CornerPoint(7).z);

	glVertex3f(BB.CornerPoint(5).x, BB.CornerPoint(5).y, BB.CornerPoint(5).z);
	glVertex3f(BB.CornerPoint(1).x, BB.CornerPoint(1).y, BB.CornerPoint(1).z);

	glVertex3f(BB.CornerPoint(5).x, BB.CornerPoint(5).y, BB.CornerPoint(5).z);
	glVertex3f(BB.CornerPoint(4).x, BB.CornerPoint(4).y, BB.CornerPoint(4).z);

	glVertex3f(BB.CornerPoint(5).x, BB.CornerPoint(5).y, BB.CornerPoint(5).z);
	glVertex3f(BB.CornerPoint(7).x, BB.CornerPoint(7).y, BB.CornerPoint(7).z);

	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(1.0f);
}

