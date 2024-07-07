#pragma once

#include "Core.h"

#define ASSERTIONS_ENABLE

#ifdef ASSERTIONS_ENABLE
#define debugBreak() __debugbreak()
#else
#define debugBreak()
#endif // ASSERTIONS_ENABLE

extern "C" BALKAN3D_API void reportAssert(bool expression, const char* message, const char* file);

#define BALKAN3D_ASSERT(expression, message)				\
		{													\
			if (!expression)								\
			{												\
				reportAssert(expression, message, __FILE__);\
				debugBreak();								\
			}												\
															\
		}													


#ifdef _DEBUG
#define BALKAN3D_ASSERT_DEBUG(expression, message)	BALKAN3D_ASSERT(expression, message)										
#else
#define BALKAN3D_ASSERT_DEBUG(expression, message)
#endif // _DEBUG
