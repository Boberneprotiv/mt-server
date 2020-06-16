#ifndef SERIAL_CLIENT_H
#define SERIAL_CLIENT_H

#include "SerialClient.h"

class PointersClient {
    private:
        SerialSlave* serialClient;
        String id;
        String lastEvent;
        String incomingEvent;

        String buildEvent(String code);

    public:
        PointersClient(String id);
        void update();

        void beginingOfTime();
        void spring();
        void summer();
        void autumn();
        void sword();
        void winterIsComming();
        void wrongWay();

        bool isReset();
};

PointersClient::PointersClient(String id) {
    this->id = id;
    this->lastEvent = this->buildEvent("00");
    this->incomingEvent = "";

    this->serialClient = new SerialSlave(this->id);
    this->serialClient->begin(0, 1, 2, 57600);
}

void PointersClient::update() {
    String iCmd = this->serialClient->read();
    
    if (iCmd == this->buildEvent("50")) {
        this->serialClient->send(this->lastEvent);
        this->lastEvent = this->buildEvent("00");
    } else {
        this->incomingEvent = iCmd;
    }
}

void PointersClient::beginingOfTime() {
  this->lastEvent = this->buildEvent("11");
}

void PointersClient::spring() {
  this->lastEvent = this->buildEvent("12");
}

void PointersClient::summer() {
  this->lastEvent = this->buildEvent("13");
}

void PointersClient::autumn() {
  this->lastEvent = this->buildEvent("14");
}

void PointersClient::sword() {
  this->lastEvent = this->buildEvent("15");
}

void PointersClient::winterIsComming() {
  this->lastEvent = this->buildEvent("16");
}

void PointersClient::wrongWay() {
  this->lastEvent = this->buildEvent("20");
}

String PointersClient::buildEvent(String code) {
    return this->id + ":" + code;
}

bool PointersClient::isReset() {
    /*if (this->incomingEvent == this->buildEvent("60")) {
        this->incomingEvent = "";
        return true;
    } else {
        return false;
    }*/
    return false;
}

#endif
