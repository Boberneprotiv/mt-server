#ifndef SERIAL_CLIENT_H
#define SERIAL_CLIENT_H

#include "SerialClient.h"

class MicrowaveClient {
    private:
        SerialSlave* serialClient;
        String id;
        String lastEvent;
        String incomingEvent;

        String buildEvent(String code);

    public:
        MicrowaveClient(String id);
        void update();

        void eggOpened();
};

MicrowaveClient::MicrowaveClient(String id) {
    this->id = id;
    this->lastEvent = this->buildEvent("00");
    this->incomingEvent = "";

    this->serialClient = new SerialSlave(this->id);
    this->serialClient->begin(4, 3, 2, 57600);
}

void MicrowaveClient::update() {
    String iCmd = this->serialClient->read();
    
    if (iCmd == this->buildEvent("50")) {
        this->serialClient->send(this->lastEvent);
        this->lastEvent = this->buildEvent("00");
    } else {
        this->incomingEvent = iCmd;
    }
}

String MicrowaveClient::buildEvent(String code) {
    return this->id + ":" + code;
}

void MicrowaveClient::eggOpened() {
    this->lastEvent = this->buildEvent("10");
}

#endif
