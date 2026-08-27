#pragma once

#include <Arduino.h>
#include "LED.h"

// Политика мигания поверх драйвера Led: знает "когда", Led знает "как".
// Состояние таймера — поле объекта, поэтому Blinker-ов может быть сколько угодно.
class Blinker {
    private:
        Led& led;
        uint32_t intervalMs;
        uint32_t lastToggleMs;

    public:
        Blinker(Led& l, uint32_t intervalMs);

        void update();   // вызывается на каждой итерации loop(), не блокирует
};
