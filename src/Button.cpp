#include <Arduino.h>
#include <FunctionalInterrupt.h>
#include "Button.h"

Button::Button(uint8_t p, uint32_t debounce) :
    pin(p),
    debounceMs(debounce),
    pressedFlag(false),
    lastPressMs(0) { }

void Button::init() {
    pinMode(pin, INPUT_PULLUP);

    // functional-interrupt поддержка ESP32 core: лямбда с this, без static trampoline
    attachInterrupt(digitalPinToInterrupt(pin), [this]() { pressedFlag = true; }, FALLING);
}

bool Button::consumePress() {
    if (!pressedFlag) {
        return false;
    }

    pressedFlag = false;

    uint32_t now = millis();
    if (now - lastPressMs < debounceMs) {   // дребезг: эхо того же нажатия
        return false;
    }
    lastPressMs = now;                      // запоминаем только принятое

    return true;
}
