#pragma once

// Warning disabled ---
#pragma warning( disable : 4577 ) // Warning that exceptions are disabled
#pragma warning( disable : 4530 ) // Warning that exceptions are disabled

#include <windows.h>
#include <stdio.h>

#define MY_LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define HAVE_M_PI

typedef unsigned int uint;
typedef unsigned __int64 uint64;

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define DEFAULT_BRIGHTNESS 1.0f
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SCREEN_SIZE 1
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE true
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true
#define CONFIG_FILE "Settings/config.json"
#define DEFAULT_SCENE_FILE "Scenes/StreetEnvironmentScene.json"
#define PI 3.1415926f
#define CHECKERS_WIDTH 64
#define CHECKERS_HEIGHT 64

#define NUM_PATHS 6
#define TEXTURES_PATH "Assets/Textures/"
#define MODELS_PATH "Assets/Models/"
#define AUDIO_PATH "Assets/Audio/"
#define LIB_TEXTURES_PATH "Library/Textures/"
#define LIB_MODELS_PATH "Library/Models/"
#define LIB_UI_PATH "Library/UI/"
#define SETTINGS_PATH "Settings/"
#define ASSETS_PATH "Assets/"
#define OWN_FILE_FORMAT ".turbox"
#define OWN_FILE_FORMAT_CAP ".TURBOX"
#define DDS_FORMAT ".dds"
#define FBX_FORMAT ".fbx"
#define FBX_FORMAT_CAP ".FBX"
#define META_FORMAT ".meta"
#define DDS_FORMAT ".dds"
#define DDS_FORMAT_CAP ".DDS"
#define FBX_FORMAT ".fbx"
#define FBX_FORMAT_CAP ".FBX"
#define PNG_FORMAT ".png"
#define PNG_FORMAT_CAP ".PNG"
#define TGA_FORMAT ".tga"
#define TGA_FORMAT_CAP ".TGA"
#define JPG_FORMAT ".jpg"
#define JPG_FORMAT_CAP ".JPG"
#define JPEG_FORMAT ".jpeg"
#define JPEG_FORMAT_CAP ".JPEG"

#define RELEASE( x )\
{\
    if( x != NULL )\
	{\
      delete x;\
	  x = NULL;\
	}\
}

#define RELEASE_ARRAY( x )\
{\
    if( x != NULL )\
	{\
      delete[] x;\
	  x = NULL;\
	}\
}

template <class T>
struct range
{
	T min; //Start
	T max; //Final
};
