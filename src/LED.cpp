#include <Arduino.h>
#include "LED.h"

Led::Led(uint8_t p) : pin(p), state(LedState::Off) { }

void Led::init() {
    pinMode(pin, OUTPUT);
    set(LedState::Off);
}

void Led::set(LedState newState) {
    state = newState;

    // enum class не конвертируется в int неявно — только явным кастом
    digitalWrite(pin, static_cast<uint8_t>(state));
}

void Led::toggle() {
    set(state == LedState::On ? LedState::Off : LedState::On);
}

LedState Led::get() const {
    return state;
}
