#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "JSON/parson.h"
#include "Globals.h"

class Config_JSON_Array;

class Config_JSON_Node
{

public:
	Config_JSON_Node();						
	Config_JSON_Node(const char* buffer);		
	Config_JSON_Node(JSON_Object* obj);		
	~Config_JSON_Node();

	void Release();
	
	float GetNumber(const char* name, double default = -1.0f);
	bool GetBool(const char* name, bool default = false);
	const char* GetString(const char* name, const char* default = "");
	Config_JSON_Array GetArray(const char* name);

	void SetNumber(const char* name, double number);
	void SetBool(const char* name, bool boolean);
	void SetString(const char* name, const char* string);
private:
	JSON_Value* root_value = nullptr;
	JSON_Object* node = nullptr;
};

class Config_JSON_Array
{
public:
	Config_JSON_Array();
	Config_JSON_Array(JSON_Array* arr);

	void AddNumber(double number);
	void AddString(char* string);
	void AddBool(bool boolean);

	Config_JSON_Node GetNodeInArray(const char* name);
	Config_JSON_Node GetNodeAt(int index);
private:
	JSON_Array* json_array;
	uint size = 0;
};

#endif //__CONFIG_H__
