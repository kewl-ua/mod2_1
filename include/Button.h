#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
    private:
        uint8_t pin;
        uint32_t debounceMs;
        uint32_t lastPressMs;

    public:
        Button(uint8_t pin, uint32_t debounceMs);

        void init();

        bool consumePress();
};

#endif // BUTTON_H
