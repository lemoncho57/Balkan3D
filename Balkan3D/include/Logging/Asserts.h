#ifndef LOGGING_ASSERTS_H
#define LOGGING_ASSERTS_H

#include "../Defines.h"

#define ASSERTIONS_ENABLE

#ifdef ASSERTIONS_ENABLE
#ifdef _MSV_VER
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif
#else
#define debugBreak()
#endif // ASSERTIONS_ENABLE

extern "C" BALKAN3D_API void reportAssert(const char* expression, const char* message, const char* file, long line);

#define BALKAN3D_ASSERT(expression, message)							\
		{																\
			if (!expression)											\
			{															\
				reportAssert(#expression, message, __FILE__, __LINE__);	\
				debugBreak();											\
			}															\
																		\
		}													

#ifdef _DEBUG
#define BALKAN3D_ASSERT_DEBUG(expression, message)	BALKAN3D_ASSERT(expression, message)										
#else
#define BALKAN3D_ASSERT_DEBUG(expression, message)
#endif // _DEBUG

#endif //LOGGING_ASSERTS_H