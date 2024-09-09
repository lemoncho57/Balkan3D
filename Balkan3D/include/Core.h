#ifndef CORE_H
#define CORE_H

#ifdef BALKAN3D_EXPORT
#ifdef _MSC_VER
#define BALKAN3D_API __declspec(dllexport)
#else
#define BALKAN3D_API __attribute__((visibility("default")))
#endif // _MSC_VER
#else
#ifdef _MSC_VER
#define BALKAN3D_API __declspec(dllimport)
#else
#define BALKAN3D_API
#endif
#endif

#define GLM_ENABLE_EXPERIMENTAL
#endif //CORE_H