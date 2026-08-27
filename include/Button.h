#pragma once

#include <Arduino.h>

class Button {
    private:
        uint8_t pin;
        uint32_t debounceMs;
        volatile bool pressedFlag;
        uint32_t lastPressMs;

    public:
        Button(uint8_t pin, uint32_t debounceMs);

        void init();

        // true не чаще одного раза на дебаунсенное нажатие
        bool consumePress();
};
