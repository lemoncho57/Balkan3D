#include "pch.h"
#include "Logging/Asserts.h"

void reportAssert(bool expression, const char* message, const char* file)
{
	LOG_FATAL("Assertion failure!: %s, message: %s, file: %s", expression, message, file);
}
