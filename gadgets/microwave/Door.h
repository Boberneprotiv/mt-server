#include <inttypes.h>

class Door {
    private:
        uint8_t pin;

    public:
        Door(uint8_t pin);
        bool isOpen();
};

Door::Door(uint8_t pin) {
    this->pin = pin;

    pinMode(this->pin, INPUT);
}

bool Door::isOpen() {
    return !digitalRead(this->pin);
}
