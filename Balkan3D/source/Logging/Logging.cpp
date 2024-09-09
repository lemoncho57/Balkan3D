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
		fprintf(stderr, "{FATAL}: ");
		break;
	case ERROR_LOG:
		fprintf(stderr, "{ERROR}: ");
		break;
	case WARNING_LOG:
		fprintf(stdout, "{WARNING}: ");
		break;
	case INFO_LOG:
		fprintf(stdout, "{INFO}: ");
		break;
	default:
		break;
	}

	vprintf(message, args);
	fprintf(type == FATAL_LOG || type == ERROR_LOG ? stderr : stdout,"\n");
	va_end(args);
}
