#include <Arduino.h>
#include "Button.h"

static volatile bool s_pressed = false;

static void IRAM_ATTR onPress() {
    s_pressed = true;
}

Button::Button(uint8_t p, uint32_t debounce) :
    pin(p),
    debounceMs(debounce),
    lastPressMs(0) { }

void Button::init() {
    pinMode(pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(pin), onPress, RISING);
}

bool Button::consumePress() {
    if (!s_pressed) {
        return false;
    }

    uint32_t now = millis();

    if (now - lastPressMs < debounceMs) {
        s_pressed = false;
        return false;
    }

    s_pressed = false;
    lastPressMs = now;
    return true;
}
