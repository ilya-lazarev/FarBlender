#ifndef FARBLENDER_H
#define FARBLENDER_H

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the FARBLENDER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// FARBLENDER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef FARBLENDER_EXPORTS
#define FARBLENDER_API __declspec(dllexport)

#include "plugin.hpp"
#define PLUGIN_VER_MAJOR   3
#define PLUGIN_VER_MINOR   11
#define PLUGIN_VER_BUILD   0
#define PLUGIN_FAR_BUILD   4040

#define PLUGIN_NAME        "Blender FS"
#define PLUGIN_AUTHOR      "Ilya Lazarev"
#define PLUGIN_DESCR       "Blender file viewer and extractor"
#define PLUGIN_FILENAME    "FarBlender.dll"

#define VSTR__(v) #v
#define VSTR(v) VSTR__(v)

#define PLUGIN_VERSION_NUM    PLUGIN_VER_MAJOR,PLUGIN_VER_MINOR,PLUGIN_VER_BUILD,PLUGIN_FAR_BUILD
#define PLUGIN_VERSION_NUM_RC PLUGIN_VER_MAJOR,PLUGIN_VER_MINOR,PLUGIN_FAR_BUILD,PLUGIN_VER_BUILD
#define PLUGIN_VERSION_TXT_RC VSTR(PLUGIN_VER_MAJOR) "." VSTR(PLUGIN_VER_MINOR) "." VSTR(PLUGIN_FAR_BUILD) "." VSTR(PLUGIN_VER_BUILD)

#else
#define FARBLENDER_API __declspec(dllimport)
#endif


#endif