#pragma once

#include <Arduino.h>

// Управление логированием на этапе КОМПИЛЯЦИИ.
// DEBUG удобно задавать флагом сборки в platformio.ini:
//     build_flags = -DDEBUG=1
// Здесь только дефолт на случай, если флаг не задан.
#ifndef DEBUG
#define DEBUG 1
#endif

#if DEBUG

#define LOG_INIT(baud)   Serial.begin(baud)
#define LOG(msg)         Serial.println(msg)
#define LOGF(fmt, ...)   Serial.printf(fmt, ##__VA_ARGS__)

#else

// В release-сборке макросы разворачиваются в пустоту: строки-литералы
// не попадают во flash, кода вызова нет вовсе — нулевая цена.
#define LOG_INIT(baud)   ((void)0)
#define LOG(msg)         ((void)0)
#define LOGF(fmt, ...)   ((void)0)

#endif
