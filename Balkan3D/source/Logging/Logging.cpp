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

	//char outMessage[32000];
	//
	//va_list args;
	//va_start(args, message);
	//vsnprintf(outMessage, 32000, message, args);
	//va_end(args);
	//sprintf_s(outMessage, "%s%s\n", typeString[type], message);
	//
	//printf("%s", outMessage);


	//va_start(args, message);
	//
	//while (*message)
	//{
	//	if (*message == '%')
	//	{
	//		if (*message == 'i')
	//			std::cout << va_arg(args, int);
	//		else if (*message == 'f')
	//			std::cout << va_arg(args, float);
	//		else if (*message == 'd')
	//			std::cout << va_arg(args, double);
	//		else if (*message == 'c')
	//			std::cout << va_arg(args, char);
	//		else if (*message == 's')
	//			std::cout << va_arg(args, char*);
	//		//std::cout << va_arg(args, void*) << "\n";
	//	}
	//	else
	//		std::cout << *message << "\n";
	//	++message;
	//}
	//va_end(args);
}
