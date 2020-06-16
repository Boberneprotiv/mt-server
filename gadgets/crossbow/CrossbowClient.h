#ifndef SERIAL_CLIENT_H
#define SERIAL_CLIENT_H

#include "SerialClient.h"

class CrossbowClient {
    private:
        SerialSlave* serialClient;
        String id;
        String lastEvent;
        String incomingEvent;

        String buildEvent(String code);

    public:
        CrossbowClient(String id);
        void update();

        void kick();
};

CrossbowClient::CrossbowClient(String id) {
    this->id = id;
    this->lastEvent = this->buildEvent("00");
    this->incomingEvent = "";

    this->serialClient = new SerialSlave(this->id);
    this->serialClient->begin(11, 12, 10, 57600);
}

void CrossbowClient::update() {
    String iCmd = this->serialClient->read();
    
    if (iCmd == this->buildEvent("50")) {
        this->serialClient->send(this->lastEvent);
        this->lastEvent = this->buildEvent("00");
    } else {
        this->incomingEvent = iCmd;
    }
}

String CrossbowClient::buildEvent(String code) {
    return this->id + ":" + code;
}

void CrossbowClient::kick() {
    this->lastEvent = this->buildEvent("10");
}

#endif
