#include <inttypes.h>

class Handle {
    private:
        uint8_t pin;
        uint8_t activation_value;

    public:
        Handle(uint8_t pin);
        bool isActive();
};

Handle::Handle(uint8_t pin) {
    this->pin = pin;
    this->activation_value = 100;

    pinMode(pin, INPUT);
}

bool Handle::isActive() {
    return analogRead(this->pin) < this->activation_value;
}
