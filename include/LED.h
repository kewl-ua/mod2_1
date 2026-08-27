#pragma once

#include <Arduino.h>

enum class LedState : uint8_t {
    Off = LOW,
    On  = HIGH
};

class Led {
    private:
        uint8_t pin;
        LedState state;

    public:
        explicit Led(uint8_t pin);

        void init();

        void set(LedState newState);
        void toggle();

        LedState get() const;
};
