#include "pch.h"
#include "Logging/Asserts.h"

void reportAssert(const char* expression, const char* message, const char* file, long line)
{
	LOG_FATAL("Assertion failure: %s, in file %s, at line %d, message %s", expression, file, line, message);
}
