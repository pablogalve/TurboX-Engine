#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "JSON/parson.h"
#include "Globals.h"

class Config_JSON_Array;

class Config_JSON_Object
{

public:
	Config_JSON_Object();						
	Config_JSON_Object(const char* buffer);		
	Config_JSON_Object(JSON_Object* obj);		
	~Config_JSON_Object();

	void Release();

	void SetNumber(const char* name, double number);
	void SetInt(const char* name, int number);
	void SetFloat(const char* name, float number);
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
	void AddInt(int number);
	void AddFloat(float number);
	void AddString(char* string);
	void AddBool(bool boolean);
private:
	JSON_Array* json_array;
	uint size = 0;
};

#endif //__CONFIG_H__
