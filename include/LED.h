enum LedState {
    OFF = LOW,
    ON = HIGH
};

class LED {
    private:
        int pin;
        LedState state;
        int durationMs;
        int delayMs;
    public:
        explicit LED(int p, int durationMs, int delayMs);

        void init();

        void on();
        void off();
        void toggle();
};
