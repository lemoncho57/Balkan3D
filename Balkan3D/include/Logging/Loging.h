#ifndef LOGGING_LOGING_H
#define LOGGING_LOGING_H
#include "../Defines.h"

typedef enum logType
{
	FATAL_LOG = 0,
	ERROR_LOG,
	WARNING_LOG,
	INFO_LOG
} logType;


bool initLogging();
void quitLogging();

extern "C" BALKAN3D_API void logOutput(logType type, const char* message, ...);

#define LOG_FATAL(message, ...)		logOutput(logType::FATAL_LOG, message, ##__VA_ARGS__);
#define LOG_ERROR(message, ...)		logOutput(logType::ERROR_LOG, message, ##__VA_ARGS__);
#define LOG_WARNING(message, ...)	logOutput(logType::WARNING_LOG, message, ##__VA_ARGS__);
#define LOG_INFO(message, ...)		logOutput(logType::INFO_LOG, message, ##__VA_ARGS__);
#endif //LOGGING_LOGING_H