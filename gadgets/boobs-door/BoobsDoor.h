#include <inttypes.h>
#include "Switch.h"
#include "Locker.h"
#include "BoobsDoorClient.h"

class BoobsDoor {
    private:
        BoobsDoorClient* serialClient;

        Switch* master_switch;
        Switch* boobs_switch[6];
        
        Locker* locker;

        bool prevStates[6];
        bool isAnyActive();
        int last_active;

    public:
        BoobsDoor(BoobsDoorClient* serialClient);
        void update();
};

BoobsDoor::BoobsDoor(BoobsDoorClient* serialClient) {
    this->serialClient = serialClient;

    this->master_switch = new Switch(A7);

    this->boobs_switch[0] = new Switch(A1);
    this->boobs_switch[1] = new Switch(A2);
    this->boobs_switch[2] = new Switch(A3);
    this->boobs_switch[3] = new Switch(A4);
    this->boobs_switch[4] = new Switch(A5);
    this->boobs_switch[5] = new Switch(A6);

    this->locker = new Locker(2, 3, 4, 5);
    this->locker->close();

    this->prevStates[0] = false;
    this->prevStates[1] = false;
    this->prevStates[2] = false;
    this->prevStates[3] = false;
    this->prevStates[4] = false;
    this->prevStates[5] = false;

    this->last_active = -1;
}

void BoobsDoor::update() {
    if (this->last_active != 100 && this->master_switch->isActive()) {
        this->last_active = 100;
        this->serialClient->openAllEvent();
        this->locker->open();
        return;
    }

    for (int boobs_index = 0; boobs_index < 6; boobs_index++) {

        bool currentState = this->boobs_switch[boobs_index]->isActive();
        if (this->last_active != boobs_index && currentState && !this->prevStates[boobs_index]) {
            this->serialClient->openEvent(boobs_index);
            this->last_active = boobs_index;
        }

        this->prevStates[boobs_index] = currentState;
    }

    if (this->isAnyActive()) {
        this->locker->close();
    }
}

bool BoobsDoor::isAnyActive() {
    return this->prevStates[0]
        || this->prevStates[1]
        || this->prevStates[2]
        || this->prevStates[3]
        || this->prevStates[4]
        || this->prevStates[5];
}
