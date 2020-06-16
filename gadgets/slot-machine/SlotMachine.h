#include <inttypes.h>
#include "Handle.h"
#include "LightLock.h"
#include "Slot.h"
#include "SlotMachineClient.h"

class SlotMachine {
    private:
        SlotMachineClient* serialClient;
        Handle* handle;
        LightLock* locks[6];
        Slot* slots[6];

        unsigned long close_time;
        unsigned long close_delay;

        int last_active;

        void closeAll();

    public:
        SlotMachine(SlotMachineClient* serialClient);
        void update();
};

SlotMachine::SlotMachine(SlotMachineClient* serialClient) {
    this->serialClient = serialClient;
    this->handle = new Handle(A1);

    this->locks[0] = new LightLock(A2);
    this->locks[1] = new LightLock(A3);
    this->locks[2] = new LightLock(A4);
    this->locks[3] = new LightLock(A5);
    this->locks[4] = new LightLock(A6);
    this->locks[5] = new LightLock(A7);

    // light on
    pinMode(A0, OUTPUT);
    digitalWrite(A0, HIGH);

    this->slots[0] = new Slot(2);
    this->slots[1] = new Slot(3);
    this->slots[2] = new Slot(4);
    this->slots[3] = new Slot(5);
    this->slots[4] = new Slot(6);
    this->slots[5] = new Slot(7);

    this->slots[0]->close();
    this->slots[1]->close();
    this->slots[2]->close();
    this->slots[3]->close();
    this->slots[4]->close();
    this->slots[5]->close();

    this->close_time = 0;
    this->close_delay = 3 * 1000; // 30 sec
    this->last_active = -1;
}

void SlotMachine::closeAll() {
  this->close_time = 0;
  this->last_active = -1;

  for (int lock_index = 0; lock_index < 6; lock_index++) {
      this->slots[lock_index]->close();
  }
}

void SlotMachine::update() {
    if (this->handle->isActive() && this->close_time < millis()) {
        for (int lock_index = 0; lock_index < 6; lock_index++) {
            if (this->last_active != lock_index && this->locks[lock_index]->isActive()) {
                this->closeAll();
                this->slots[lock_index]->open();
                this->serialClient->openEvent(lock_index);
                this->close_time = millis() + this->close_delay;
                this->last_active = lock_index;
                return;
            }
        }
    }

    if (this->close_time <= millis()) {
        this->closeAll();
    }
}
