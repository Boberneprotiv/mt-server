#ifndef SERIAL_CLIENT_H
#define SERIAL_CLIENT_H

#include "SerialClient.h"

class BoobsDoorClient {
    private:
        SerialSlave* serialClient;
        String id;
        String lastEvent;

        String buildEvent(String code);

    public:
        BoobsDoorClient(String id);
        void update();

        void openEvent(int number);
        void openAllEvent();
};

BoobsDoorClient::BoobsDoorClient(String id) {
    this->id = id;

    this->lastEvent = this->buildEvent("00");

    this->serialClient = new SerialSlave(this->id);
    this->serialClient->begin(8, 10, 9, 57600);
}

void BoobsDoorClient::update() {
    String iCmd = this->serialClient->read();
    
    if (iCmd == this->buildEvent("50")) {
        this->serialClient->send(this->lastEvent);
        this->lastEvent = this->buildEvent("00");
    }
}

void BoobsDoorClient::openEvent(int number) {
    this->lastEvent = this->buildEvent("1" + String(number));
}

void BoobsDoorClient::openAllEvent() {
    this->lastEvent = this->buildEvent("16");
}

String BoobsDoorClient::buildEvent(String code) {
    return this->id + ":" + code;
}

#endif
