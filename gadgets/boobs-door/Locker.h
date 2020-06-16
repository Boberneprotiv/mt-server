#include <inttypes.h>

class Locker {
    private:
        uint8_t pin1;
        uint8_t pin2;
        uint8_t pin3;
        uint8_t pin4;

    public:
        Locker(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);
        void open();
        void close();
};

Locker::Locker(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->pin3 = pin3;
    this->pin4 = pin4;

    pinMode(this->pin1, OUTPUT);
    pinMode(this->pin2, OUTPUT);
    pinMode(this->pin3, OUTPUT);
    pinMode(this->pin4, OUTPUT);

    this->close();
}

void Locker::open() {
    digitalWrite(this->pin1, LOW);
    digitalWrite(this->pin2, LOW);
    digitalWrite(this->pin3, LOW);
    digitalWrite(this->pin4, LOW);
}

void Locker::close() {
    digitalWrite(this->pin1, HIGH);
    digitalWrite(this->pin2, LOW);
    digitalWrite(this->pin3, HIGH);
    digitalWrite(this->pin4, LOW);
}
