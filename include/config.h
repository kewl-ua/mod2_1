#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#define DEBUG 1
#define SHOULD_LOOP_REPORT 0

struct Config {
    static constexpr uint8_t LED_PIN = 27;
    static constexpr uint8_t BUTTON_PIN = 5;

    static constexpr uint32_t BLINK_INTERVAL_MS = 1000;

    static constexpr uint32_t DEBOUNCE_MS = 200;

    static constexpr uint8_t SHORT_PRESS_BLINKS = 3;

    static constexpr unsigned long SERIAL_BAUD = 115200;
    static constexpr uint32_t LOOP_REPORT_EVERY = 1000;
};

#endif // CONFIG_H
