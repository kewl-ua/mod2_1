#include <Arduino.h>
#include "config.h"
#include "LED.h"
#include "Blinker.h"
#include "Log.h"

// Режимы работы LED, переключаются по кругу нажатием кнопки
enum class LedMode : uint8_t {
    Blinking,
    AlwaysOn,
    AlwaysOff
};

// State
Led led(Config::LED_PIN);
Blinker blinker(led, Config::BLINK_INTERVAL_MS);

static LedMode mode = LedMode::Blinking;
volatile bool buttonPressed = false;

void IRAM_ATTR onButtonPressed() {
    buttonPressed = true;
}

// API
static void handleButton();
static void applyNextMode();
static void loopTimeReport();

// Main
void setup() {
    LOG_INIT(Config::SERIAL_BAUD);

    led.init();

    pinMode(Config::BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(Config::BUTTON_PIN), onButtonPressed, FALLING);
}

void loop() {
    handleButton();

    if (mode == LedMode::Blinking) {
        blinker.update();
    }

    loopTimeReport();
}

// Implementations
static void handleButton() {
    if (!buttonPressed) {
        return;
    }

    buttonPressed = false;

    static uint32_t lastPressMs = 0;

    uint32_t now = millis();
    if (now - lastPressMs < Config::DEBOUNCE_MS) {   // дребезг: эхо того же нажатия
        return;
    }
    lastPressMs = now;                               // запоминаем только принятое

    LOGF("button pressed, lastPressMs: %lu\n", static_cast<unsigned long>(lastPressMs));

    applyNextMode();
}

static void applyNextMode() {
    switch (mode) {
        case LedMode::Blinking:
            mode = LedMode::AlwaysOn;
            led.set(LedState::On);
            LOG("mode: always on");
            break;

        case LedMode::AlwaysOn:
            mode = LedMode::AlwaysOff;
            led.set(LedState::Off);
            LOG("mode: always off");
            break;

        case LedMode::AlwaysOff:
            mode = LedMode::Blinking;
            LOG("mode: blinking");
            break;
    }
}

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
