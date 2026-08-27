#include <Arduino.h>
#include "LED.h"

LED::LED(int p, int durMs, int delMs) :
    pin(p),
    state(OFF),
    durationMs(durMs),
    delayMs(delMs) { }

void LED::init() {
    pinMode(pin, OUTPUT);
}

void LED::on() {
    state = ON;
    digitalWrite(pin, state);
}

void LED::off() {
    state = OFF;
    digitalWrite(pin, state);
}

void LED::toggle() {
    state = (state == ON) ? OFF : ON;

    digitalWrite(pin, state);
}
