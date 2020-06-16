#include <inttypes.h>

class LightLock {
    private:
        uint8_t pin;
        uint8_t activation_value;

    public:
        LightLock(uint8_t pin);
        bool isActive();
};

LightLock::LightLock(uint8_t pin) {
    this->pin = pin;
    this->activation_value = 10;

    pinMode(pin, INPUT);
}

bool LightLock::isActive() {
    return analogRead(this->pin) > this->activation_value;
}
