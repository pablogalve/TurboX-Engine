#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Globals.h"
#include "Math.h"
#include "JSON/parson.h"

class Config
{
public:
	Config();
	Config(const char* jsonName);
	Config(JSON_Object* section);
	~Config();

	uint Save(char** buffer) const;

	double GetNumber(const char* field, double default = 0.0, int index = -1) const;
	bool GetBool(const char* field, bool default, int index = -1) const;
	const char* GetString(const char* field, const char* default = nullptr, int index = -1) const;

	uint GetArraySize(const char* field) const;
	Config GetArray(const char* field, int index) const;

private:
	JSON_Value* FindValue(const char* field, int index) const;

private:

	JSON_Value* valueRoot = nullptr;
	JSON_Object* root = nullptr;
	JSON_Array* array = nullptr;

	bool to_delete = false;
};
#endif //__CONFIG_H__