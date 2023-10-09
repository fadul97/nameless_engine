#ifndef LOGGER_H
#define LOGGER_H

#include "defines.h"
#include "error_list.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define LOG_FATAL_ENABLED 1
#define LOG_ERROR_ENABLED 1

#define NE_RELEASE 0

#if NE_RELEASE == 1
#define LOG_WARN_ENABLED 0
#define LOG_DEBUG_ENABLED 0
#define LOG_INFO_ENABLED 0
#else
#define LOG_WARN_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_INFO_ENABLED 1
#endif

typedef enum LogLevel
{
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_DEBUG = 3,
    LOG_LEVEL_INFO = 4,
} LogLevel;

#ifndef LOG_FATAL
#define LOG_FATAL(error, message, ...) log_output(LOG_LEVEL_FATAL, error, message, ##__VA_ARGS__);
#endif

#ifndef LOG_ERROR
#define LOG_ERROR(error, message, ...) log_output(LOG_LEVEL_ERROR, error, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
#define LOG_WARN(message, ...) log_output(LOG_LEVEL_WARN, 0, message, ##__VA_ARGS__);
#else
#define LOG_WARN(message, ...);
#endif

#if LOG_DEBUG_ENABLED == 1
#define LOG_DEBUG(message, ...) log_output(LOG_LEVEL_DEBUG, 0, message, ##__VA_ARGS__);
#else
#define LOG_DEBUG(message, ...);
#endif

#if LOG_INFO_ENABLED == 1
#define LOG_INFO(message, ...) log_output(LOG_LEVEL_INFO, 0, message, ##__VA_ARGS__);
#else
#define LOG_INFO(message, ...);
#endif

// void log_output(LogLevel level, enum Error err, const char* message, ...);

namespace Logger
{
    void log_output(LogLevel level, ErrorCode err, const char* message, ...)
    {
        // Setup for sprintf and then printf
        char out_msg[1000];
        char out_msg2[1000];
        memset(out_msg, 0, sizeof(out_msg));

        va_list arg_ptr;
        va_start(arg_ptr, message);
        vsnprintf(out_msg, 1000, message, arg_ptr);

        /* Colors(Linux only) */
        const char *default_color = "\033[0m";

        // Bold red, Red, Orange, Blue, Green
        const char *color_strings[5] = {
            "\033[1;31m", "\033[0;31m", "\033[0;33m", "\033[0;34m", "\033[0;32m"
        };
        
        const char* level_strings[5] = {
            "[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[DEBUG]: ", "[INFO]: "
        };

        // FATAL or ERROR log
        if(level < 2)
        {
            sprintf(out_msg2, "%s%s - %s", level_strings[level], error_names[err], out_msg);
            printf("%s%s%s\n", color_strings[level], out_msg2, default_color);
            return;
        }

        sprintf(out_msg2, "%s%s", level_strings[level], out_msg);
        printf("%s%s%s\n", color_strings[level], out_msg2, default_color);
    }
}


#endif // LOGGER_H