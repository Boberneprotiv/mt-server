#include <inttypes.h>
#include "MicrowaveClient.h"
#include "Door.h"
#include "StartButton.h"
#include "Engine.h"
#include "IR.h"

class Microwave {
    private:
        MicrowaveClient* serialClient;

        Door* door;
        StartButton* startButton;
        Engine* engine;
        IR* ir;

        bool isCooking;
        unsigned long cookingTime;

    public:
        Microwave(MicrowaveClient* serialClient);
        void update();
};

Microwave::Microwave(MicrowaveClient* serialClient) {
    this->serialClient = serialClient;
    this->door = new Door(13);
    this->startButton = new StartButton(9);
    this->engine = new Engine(11);
    this->ir = new IR(10);

    this->isCooking = false;
    this->cookingTime = 0;
}

void Microwave::update() {

    if (this->isCooking) {
        this->engine->start();
    } else {
        this->engine->stop();
        this->ir->off();
    }

    if (this->door->isOpen()) {
        this->isCooking = false;
        this->cookingTime = 0;
        return;
    }

    if (!this->isCooking && this->startButton->isActive()) {
        // activate
        this->isCooking = true;
        this->cookingTime = millis() + 10 * 1000; // 10 sec

        return;
    }

    if (this->isCooking) {
        
        if (millis() > this->cookingTime) {
            // deactivate
            this->isCooking = false;
            this->cookingTime = 0;
            this->serialClient->eggOpened();
        }
        
        if (this->isCooking && millis() > this->cookingTime - 2000) {
            // blinking

            /*if (millis() % 100 > 50) {
                this->ir->on();
            } else {
                this->ir->off();
            }*/

            this->ir->on();
        }

        return;
    }
    
    this->isCooking = false;
    this->cookingTime = 0;
}
