#include <inttypes.h>

class StartButton {
    private:
        uint8_t pin;

    public:
        StartButton(uint8_t pin);
        bool isActive();
};

StartButton::StartButton(uint8_t pin) {
    this->pin = pin;

    pinMode(this->pin, INPUT);
}

bool StartButton::isActive() {
    return !digitalRead(this->pin);
}
