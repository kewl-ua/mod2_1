#ifndef LOG_H
#define LOG_H

#include <Arduino.h>

#if DEBUG

#define LOG_INIT(baud)   Serial.begin(baud)
#define LOG(msg)         Serial.println(msg)
#define LOGF(fmt, ...)   Serial.printf(fmt, ##__VA_ARGS__)

#else

#define LOG_INIT(baud)   ((void)0)
#define LOG(msg)         ((void)0)
#define LOGF(fmt, ...)   ((void)0)

#endif

#endif // LOG_H
