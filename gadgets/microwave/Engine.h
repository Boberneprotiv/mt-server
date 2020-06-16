#include <inttypes.h>

class Engine {
    private:
        uint8_t pin;

    public:
        Engine(uint8_t pin);
        void start();
        void stop();
};

Engine::Engine(uint8_t pin) {
    this->pin = pin;

    pinMode(pin, OUTPUT);
}

void Engine::start() {
    digitalWrite(this->pin, HIGH);
}

void Engine::stop() {
    digitalWrite(this->pin, LOW);
}
