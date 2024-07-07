#include "pch.h"
#include "Logging/Asserts.h"

void reportAssert(bool expression, const char* message, const char* file, long line)
{
	LOG_FATAL("Assertion failure in: %s at line %d because %s, message: %s", file, line, expression ? "false" : "true", message);
}
