#include <inttypes.h>

class Light {
    private:
        uint8_t led_pin;
        uint8_t spark_pin;
        unsigned long start_of_activation;
        unsigned long activation_time;

    public:
        Light(uint8_t led_pin, uint8_t spark_pin);
        void update();
        void activate();
};

Light::Light(uint8_t led_pin, uint8_t spark_pin) {
    this->led_pin = led_pin;
    this->spark_pin = spark_pin;
    this->activation_time = 0;

    // set output
    pinMode(this->led_pin, OUTPUT);
    pinMode(this->spark_pin, OUTPUT);
}

void Light::update() {
    if (this->activation_time < millis()) {
        this->start_of_activation = 0;
        this->activation_time = 0;
        digitalWrite(this->led_pin, LOW);
        digitalWrite(this->spark_pin, LOW);
        
        return;
    }

    digitalWrite(this->spark_pin, HIGH);

    unsigned long from_start_to_now = (millis() - this->start_of_activation) / 300;
    if (from_start_to_now % 2 == 0) {
        digitalWrite(this->led_pin, HIGH);
    } else {
        digitalWrite(this->led_pin, LOW);
    }
}

void Light::activate() {
    this->start_of_activation = millis();
    this->activation_time = millis() + 2 * 1000; // 2 sec
}
