#include <Arduino.h>
#include "Blinker.h"

Blinker::Blinker(Led& l, uint32_t interval) :
    led(l),
    intervalMs(interval),
    lastToggleMs(0) { }

void Blinker::update() {
    uint32_t now = millis();

    if (now - lastToggleMs >= intervalMs) {
        lastToggleMs = now;
        led.toggle();
    }
}
