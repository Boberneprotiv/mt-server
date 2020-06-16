#include <inttypes.h>

class IR {
    private:
        uint8_t pin;

    public:
        IR(uint8_t pin);
        void on();
        void off();
};

IR::IR(uint8_t pin) {
    this->pin = pin;

    pinMode(pin, OUTPUT);
}

void IR::on() {
    digitalWrite(this->pin, HIGH);
}

void IR::off() {
    digitalWrite(this->pin, LOW);
}
