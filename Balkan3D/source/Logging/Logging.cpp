#include "pch.h"
#include "Logging/Loging.h"

#define COLOR_WHITE "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"

#define BACKGROUND_RED "\033[41m"

bool initLogging()
{

	return true;
}

void quitLogging()
{

}

void logOutput(logType type, const char* message, ...)
{
	va_list args;
	va_start(args, message);

	switch (type)
	{
	case FATAL_LOG:
		fprintf(stderr, BACKGROUND_RED "{FATAL}: ");
		break;
	case ERROR_LOG:
		fprintf(stderr, COLOR_RED "{ERROR}: ");
		break;
	case WARNING_LOG:
		fprintf(stdout, COLOR_YELLOW "{WARNING}: ");
		break;
	case INFO_LOG:
		fprintf(stdout, COLOR_GREEN "{INFO}: ");
		break;
	case DEBUG_LOG:
		fprintf(stdout, COLOR_BLUE "{DEBUG}: ");
		break;
	default:
		break;
	}

	vprintf(message, args);
	fprintf(stdout, COLOR_WHITE "\n");
	va_end(args);
}
