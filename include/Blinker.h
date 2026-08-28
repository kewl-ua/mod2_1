#ifndef BLINKER_H
#define BLINKER_H

#include <Arduino.h>
#include "LED.h"

class Blinker {
    private:
        Led& led;
        uint32_t intervalMs;
        uint32_t lastToggleMs;

    public:
        Blinker(Led& l, uint32_t intervalMs);

        void update();
        void reset();
};

#endif // BLINKER_H