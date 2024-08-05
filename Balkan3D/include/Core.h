#pragma once

#ifdef BALKAN3D_EXPORT
#define BALKAN3D_API __declspec(dllexport)
#else
#define BALKAN3D_API __declspec(dllimport)
#endif