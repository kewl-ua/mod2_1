#include <Arduino.h>
#include "config.h"
#include "LED.h"
#include "Blinker.h"
#include "Button.h"
#include "Log.h"

enum class LedMode : uint8_t {
    Blinking,
    AlwaysOn,
    AlwaysOff
};

// State
static LedMode mode = LedMode::Blinking;

// LED instance representing the physical LED on the board
Led led(Config::LED_PIN);

// Controls blinking logic for each LED
Blinker blinker(led, Config::BLINK_INTERVAL_MS);

// Controls button input and debouncing logic
Button button(Config::BUTTON_PIN, Config::DEBOUNCE_MS);


// API
static void handleButton();
static LedMode nextMode(LedMode current);
static void enterMode(LedMode newMode);
static void updateMode();
static void loopTimeReport();

// Main
void setup() {
    LOG_INIT(Config::SERIAL_BAUD);

    led.init();
    button.init();
}

void loop() {
    handleButton();
    updateMode();

    #if SHOULD_LOOP_REPORT
        loopTimeReport();
    #endif
}

// Implementations
static void handleButton() {
    if (!button.consumePress()) {
        return;
    }

    LOGF("button pressed, now: %lu\n", static_cast<unsigned long>(millis()));

    enterMode(nextMode(mode));
}

// Чистый расчёт следующего режима, без побочных эффектов
static LedMode nextMode(LedMode current) {
    switch (current) {
        case LedMode::Blinking:  return LedMode::AlwaysOn;
        case LedMode::AlwaysOn:  return LedMode::AlwaysOff;
        case LedMode::AlwaysOff: return LedMode::Blinking;
    }
    return LedMode::Blinking;   // недостижимо, но глушит warning о пути без return
}

// Action on entering a new mode
static void enterMode(LedMode newMode) {
    mode = newMode;

    switch (mode) {
        case LedMode::Blinking:
            blinker.reset();   // фаза мигания всегда стартует заново
            LOG("mode: blinking");
            break;

        case LedMode::AlwaysOn:
            led.set(LedState::On);
            LOG("mode: always on");
            break;

        case LedMode::AlwaysOff:
            led.set(LedState::Off);
            LOG("mode: always off");
            break;
    }
}

// Periodic action for the current LED mode
static void updateMode() {
    switch (mode) {
        case LedMode::Blinking:
            blinker.update();
            break;

        case LedMode::AlwaysOn:
        case LedMode::AlwaysOff:
            break;
    }
}

// Reports the average loop time every Config::LOOP_REPORT_EVERY iterations
static void loopTimeReport() {
    static uint32_t iterations = 0;
    static uint32_t windowStartUs = micros();

    ++iterations;

    if (iterations >= Config::LOOP_REPORT_EVERY) {
        uint32_t elapsedUs = micros() - windowStartUs;

        LOGF("superloop: %lu iterations, avg %.2f us/iter\n",
             static_cast<unsigned long>(iterations),
             static_cast<double>(elapsedUs) / iterations);

        iterations = 0;
        windowStartUs = micros();
    }
}
