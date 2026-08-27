#pragma once

#include <Arduino.h>

struct Config {
    static constexpr uint8_t LED_PIN = 27;
    static constexpr uint8_t BUTTON_PIN = 4;

    static constexpr uint32_t BLINK_INTERVAL_MS = 1000;

    static constexpr uint32_t DEBOUNCE_MS = 200;   // защита от дребезга контактов кнопки

    static constexpr uint8_t SHORT_PRESS_BLINKS = 3;   // пример доп. настройки под будущую кнопку

    static constexpr unsigned long SERIAL_BAUD = 115200;
    static constexpr uint32_t LOOP_REPORT_EVERY = 1000;
};
