#ifndef CORE_H
#define CORE_H
#ifdef BALKAN3D_EXPORT
#define BALKAN3D_API __declspec(dllexport)
#else
#define BALKAN3D_API __declspec(dllimport)
#endif

#define GLM_ENABLE_EXPERIMENTAL
#endif //CORE_H