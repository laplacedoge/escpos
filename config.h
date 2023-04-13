#ifndef __CONFIG_H__
#define __CONFIG_H__

#define CONF_USE_LOGGING

#ifdef CONF_USE_LOGGING
#include <stdio.h>
#include <stdarg.h>
#endif

#define CONF_USE_GLOBAL_LOG_LEVEL

#ifdef CONF_USE_GLOBAL_LOG_LEVEL
#define CONF_GLOBAL_LOG_LEVEL       5
#endif

#define CONF_LOG_SUFFIX             "\r\n"

#define CONF_LOG_PROTOTYPE(module, format, ...) \
    printf("[" module "] " format CONF_LOG_SUFFIX, ##__VA_ARGS__)

#define CONF_LOG(module, format, ...) \
    CONF_LOG_PROTOTYPE(module, format, ##__VA_ARGS__)

#define CONF_ASSERT(module, expr)   if (!(expr)) { CONF_LOG(module, "failed assertion \"%s\": %s:%d", \
                                                            #expr, __FILE__, __LINE__); }

#define LOG_NONE    0
#define LOG_ERROR   1
#define LOG_WARN    2
#define LOG_INFO    3
#define LOG_DEBUG   4
#define LOG_ASSERT  5

#endif
