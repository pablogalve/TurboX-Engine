#include "Config_JSON.h"

Config_JSON_Object::Config_JSON_Object()
{
	root_value = json_value_init_object();
	node = json_value_get_object(root_value);
}

Config_JSON_Object::Config_JSON_Object(const char* buffer)
{
	root_value = json_parse_string(buffer);
	if (root_value)
	{
		node = json_value_get_object(root_value);
	}
}

Config_JSON_Object::Config_JSON_Object(JSON_Object* obj) : node(obj)
{
}

Config_JSON_Object::~Config_JSON_Object()
{
	Release();
}

void Config_JSON_Object::Release()
{
	if (root_value)	
		json_value_free(root_value);	
}

void Config_JSON_Object::SetNumber(const char* name, double number)
{
	json_object_set_number(node, name, number);
}

void Config_JSON_Object::SetInt(const char* name, int number)
{
	SetNumber(name, (double)number);
}

void Config_JSON_Object::SetFloat(const char* name, float number)
{
	SetNumber(name, (double)number);
}

void Config_JSON_Object::SetBool(const char* name, bool boolean)
{
	json_object_set_boolean(node, name, boolean);
}

void Config_JSON_Object::SetString(const char* name, const char* string)
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

void Config_JSON_Array::AddInt(int number)
{
	AddNumber((double)number);
}

void Config_JSON_Array::AddFloat(float number)
{
	AddNumber((double)number);
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