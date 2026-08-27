#include <Arduino.h>
#include "LED.h"

// Constants
constexpr int LED_PIN = 19;
constexpr int BLINK_DURATION = 1000;
constexpr int BLINK_DELAY = 1000;

LED led(LED_PIN, BLINK_DURATION, BLINK_DELAY);

volatile bool ledRequested = false;

hw_timer_t* timer = NULL;

void myDelay(uint32_t duration);

void IRAM_ATTR onTimer() {
    ledRequested = true;

    timerWrite(timer, 0);
}

// Main
void setup() {
    led.init();

    timer = timerBegin(0, 80, true);

    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, BLINK_DELAY * 1000, true);
    timerAlarmEnable(timer);
}

void loop() {
    if (ledRequested) {
        led.toggle();
        ledRequested = false;

        Serial.println("LED toggled");
    }
}
