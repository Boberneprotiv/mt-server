#include <inttypes.h>

class Slot {
    private:
        uint8_t pin;

    public:
        Slot(uint8_t pin);
        void open();
        void close();
};

Slot::Slot(uint8_t pin) {
    this->pin = pin;

    pinMode(pin, OUTPUT);
}

void Slot::open() {
    digitalWrite(this->pin, HIGH);
}

void Slot::close() {
    digitalWrite(this->pin, LOW);
}
