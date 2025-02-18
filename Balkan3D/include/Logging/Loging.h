#ifndef LOGGING_LOGING_H
#define LOGGING_LOGING_H
#include "../Defines.h"

typedef enum logType
{
	FATAL_LOG = 0,
	ERROR_LOG,
	WARNING_LOG,
	INFO_LOG,
	DEBUG_LOG
} logType;


bool initLogging();
void quitLogging();


extern "C" BALKAN3D_API void logOutput(logType type, const char* message, ...);

#define LOG_FATAL(message, ...)		logOutput(logType::FATAL_LOG, message, ##__VA_ARGS__);
#define LOG_ERROR(message, ...)		logOutput(logType::ERROR_LOG, message, ##__VA_ARGS__);
#define LOG_WARNING(message, ...)	logOutput(logType::WARNING_LOG, message, ##__VA_ARGS__);
#define LOG_INFO(message, ...)		logOutput(logType::INFO_LOG, message, ##__VA_ARGS__);
#if defined(DEBUG) || defined(_DEBUG)
#define LOG_DEBUG(message, ...) 	logOutput(logType::DEBUG_LOG, message, ##__VA_ARGS__);
#else
#define LOG_DEBUG(message, ...)
#endif
#endif //LOGGING_LOGING_H