#include <inttypes.h>
#include "SoftwareSerial.h"

class SerialSlave {
  private:
    SoftwareSerial *softPort;
    uint8_t serialPin;
    String id;

    void setupReceiveMode();
    void setupTransmiteMode();

  public:
    SerialSlave(String id);
    void begin(uint8_t rx, uint8_t tx, uint8_t pin, long speed);
    void send(String str);
    String read();
};

SerialSlave::SerialSlave(String id) {
  this->id = id;
}

void SerialSlave::begin(uint8_t rx, uint8_t tx, uint8_t pin, long speed) {
  this->serialPin = pin;

  softPort = new SoftwareSerial(rx, tx);
  softPort->begin(speed);

  softPort->setTimeout(50);

  pinMode(this->serialPin, OUTPUT);
  setupReceiveMode();
}

void SerialSlave::send(String str) {
  this->setupTransmiteMode();
  this->softPort->println(str);
  delay(10);
  this->setupReceiveMode();
}

String SerialSlave::read() {
  if (this->softPort->available()) {
    String message = this->softPort->readString();

    return message;
  }

  return "";
}

void SerialSlave::setupReceiveMode() {
  digitalWrite(serialPin, LOW);
}

void SerialSlave::setupTransmiteMode() {
  digitalWrite(serialPin, HIGH);
}


