#include "Config_JSON.h"
#include "Application.h"
#include "ModuleConsole.h"

Config_JSON_Node::Config_JSON_Node()
{
	root_value = json_value_init_object();
	node = json_value_get_object(root_value);
}

Config_JSON_Node::Config_JSON_Node(const char* buffer)
{
	root_value = json_parse_string(buffer);
	if (root_value)
	{
		node = json_value_get_object(root_value);
	}
}

Config_JSON_Node::Config_JSON_Node(JSON_Object* obj) : node(obj)
{
}

Config_JSON_Node::~Config_JSON_Node()
{
	Release();
}

void Config_JSON_Node::Release()
{
	//if (root_value)	
	//	json_value_free(root_value);	
}

float Config_JSON_Node::GetNumber(const char* name, double default)
{
	if (json_object_has_value(node, name) == 1)
		return json_object_get_number(node, name);
	else
		return default;
}

bool Config_JSON_Node::GetBool(const char* name, bool default)
{
	if (json_object_has_value(node, name) == 1)
		return json_object_get_boolean(node, name);
	else
		return default;
}

const char* Config_JSON_Node::GetString(const char* name, const char* default)
{
	if (json_object_has_value(node, name) == 1)
		return json_object_get_string(node, name);
	else
		return default;
}

Config_JSON_Array Config_JSON_Node::GetArray(const char* name)
{
	if (json_object_has_value(node, name) == 1)
		return json_object_get_array(node, name);
	else
		return nullptr;	
}

void Config_JSON_Node::SetNumber(const char* name, double number)
{
	json_object_set_number(node, name, number);
}

void Config_JSON_Node::SetBool(const char* name, bool boolean)
{
	json_object_set_boolean(node, name, boolean);
}

void Config_JSON_Node::SetString(const char* name, const char* string)
{
	json_object_set_string(node, name, string);
}

Config_JSON_Array::Config_JSON_Array()
{
	json_array = json_value_get_array(json_value_init_array());
}

Config_JSON_Array::Config_JSON_Array(JSON_Array* arr)
{
	json_array = nullptr;
	size = json_array_get_count(arr);
}

void Config_JSON_Array::AddNumber(double number)
{
	json_array_append_number(json_array, number);
	size++;
}

void Config_JSON_Array::AddString(char* string)
{
	json_array_append_string(json_array, string);
	size++;
}

void Config_JSON_Array::AddBool(bool boolean)
{
	json_array_append_boolean(json_array, boolean);
	size++;
}

Config_JSON_Node Config_JSON_Array::GetNodeInArray(const char* name)
{
	for (size_t i = 0; i < json_array_get_count(json_array); i++)
	{
		JSON_Object* object = json_array_get_object(json_array, i);
		const char* object_name = json_object_get_string(object, "name");

		if (strcmp(name, object_name) == 0)
			return Config_JSON_Node(object);
	}
	
	App->console->AddLog("JSON node '%s' could not be found", name);
}

Config_JSON_Node Config_JSON_Array::GetNodeAt(int index)
{
	JSON_Object* object = json_array_get_object(json_array, index);
	return Config_JSON_Node(object);
}