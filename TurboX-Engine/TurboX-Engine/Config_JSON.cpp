#include "Config_JSON.h"

//#include "mmgr/mmgr.h"

Config::Config()
{
	valueRoot = json_value_init_object();
	root = json_value_get_object(valueRoot);
	to_delete = true;
}


Config::Config(const char* jsonName)
{
	valueRoot = json_parse_string(jsonName);
	if (valueRoot != nullptr) {
		root = json_value_get_object(valueRoot);
		to_delete = true;
	}
}

Config::Config(JSON_Object* section) : root(section)
{}


Config::~Config()
{
	if (to_delete == true) {
		json_value_free(valueRoot);
	}
}

uint Config::Save(char** buffer) const
{
	uint written = json_serialization_size(valueRoot);
	*buffer = new char[written];
	json_serialize_to_buffer(valueRoot, *buffer, written);
	return written;
}

JSON_Value* Config::FindValue(const char* field, int index) const
{
	if (index < 0) {
		return json_object_get_value(root, field);
	}

	JSON_Array* array = json_object_get_array(root, field);
	if (array != nullptr) {
		return json_array_get_value(array, index);
	}
	return nullptr;
}

double Config::GetNumber(const char* field, double default, int index) const
{
	JSON_Value* value = FindValue(field, index);

	if (value && json_value_get_type(value) == JSONNumber) {
		return json_value_get_number(value);
	}

	return default;
}

bool Config::GetBool(const char* field, bool default, int index) const
{
	JSON_Value* value = FindValue(field, index);

	if (value && json_value_get_type(value) == JSONBoolean) {
		return json_value_get_boolean(value) != 0;
	}

	return default;
}

const char* Config::GetString(const char* field, const char* default, int index) const
{
	JSON_Value* value = FindValue(field, index);

	if (value && json_value_get_type(value) == JSONString) {
		return json_value_get_string(value);
	}

	return default;
}

uint Config::GetArraySize(const char* field) const
{
	JSON_Array* array = json_object_get_array(root, field);
	if (array == nullptr) {
		return -1;
	}
	int num = json_array_get_count(array);
	return num;
}

Config Config::GetArray(const char* field, int index) const
{
	JSON_Array* array = json_object_get_array(root, field);
	if (array != nullptr) {
		return Config(json_array_get_object(array, index));
	}
	return Config((JSON_Object*) nullptr);
}