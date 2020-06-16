#include <inttypes.h>
#include "CrossbowClient.h"

class Crossbow {
    private:
        CrossbowClient* serialClient;
        unsigned long disable_time;
        unsigned long closing_time;

    public:
        Crossbow(CrossbowClient* serialClient);
        void update();
};

Crossbow::Crossbow(CrossbowClient* serialClient) {
    this->serialClient = serialClient;
    this->disable_time = 0;
    this->closing_time = 0;

    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
}

void Crossbow::update() {
    unsigned long now = millis();

    if (this->closing_time < now) {
        digitalWrite(3, LOW);
        this->closing_time = 0;
    }
    
    if (this->disable_time > now) {
        return;
    }

    if (digitalRead(4)) {
        this->serialClient->kick();
        this->disable_time = millis() + 30 * 1000; // 30 sec to next kick
        this->closing_time = millis() + 600; // 600 ms to close locker
        digitalWrite(3, HIGH);
    }
}
