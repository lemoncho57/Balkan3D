#include "pch.h"
#include "Logging/Loging.h"

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
		printf("{FATAL}: ");
		break;
	case ERROR_LOG:
		printf("{ERROR}: ");
		break;
	case WARNING_LOG:
		printf("{WARNING}: ");
		break;
	case INFO_LOG:
		printf("{INFO}: ");
		break;
	default:
		break;
	}

	vprintf(message, args);
	printf("\n");
	va_end(args);
}
