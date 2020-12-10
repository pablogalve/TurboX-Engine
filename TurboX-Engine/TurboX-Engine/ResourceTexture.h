#ifndef __RESOURCE_TEXTURE_H__
#define __RESOURCE_TEXTURE_H__

#include "Globals.h"
#include "Resource.h"

class Config;

class ResourceTexture :	public Resource
{
	enum Format {
		color_index,
		rgb,
		rgba,
		bgr,
		bgra,
		luminance,
		unknown
	};

public:
	ResourceTexture(uint UUID);
	virtual ~ResourceTexture();

	void LoadInMemory() override;
	void FreeInMemory() override;
	void Save(Config& config) const override;
	void Load(const Config& config) override; 
	void CleanUp() override;

public:
	uint width = 0;
	uint height = 0;
	uint gpuID = 0;

	
	Format format = unknown;
};

#endif// !__RESOURCE_TEXTURE_H__
