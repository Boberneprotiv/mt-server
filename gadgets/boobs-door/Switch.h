#include <inttypes.h>

class Switch {
    private:
        uint8_t pin;
        int activation_value;
        int a_delay;

    public:
        Switch(uint8_t pin);
        bool isActive();
};

Switch::Switch(uint8_t pin) {
    this->pin = pin;
    this->a_delay = 300;
    this->activation_value = 512;
}

bool Switch::isActive() {
    return analogRead(this->pin) < this->activation_value;
}
