#ifndef SERIAL_CLIENT_H
#define SERIAL_CLIENT_H

#include "SerialClient.h"

class SparkGeneratorClient {
    private:
        SerialSlave* serialClient;
        String id;
        String lastEvent;

        String buildEvent(String code);

    public:
        SparkGeneratorClient(String id);
        void update();

        void spark();
};

SparkGeneratorClient::SparkGeneratorClient(String id) {
    this->id = id;

    this->lastEvent = this->buildEvent("00");

    this->serialClient = new SerialSlave(this->id);
    this->serialClient->begin(11, 12, 10, 57600);
}

void SparkGeneratorClient::update() {
    String iCmd = this->serialClient->read();
    
    if (iCmd == this->buildEvent("50")) {
        this->serialClient->send(this->lastEvent);
        this->lastEvent = this->buildEvent("00");
    }
}

void SparkGeneratorClient::spark() {
    this->lastEvent = this->buildEvent("10");
}

String SparkGeneratorClient::buildEvent(String code) {
    return this->id + ":" + code;
}

#endif
