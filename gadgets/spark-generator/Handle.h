#include <inttypes.h>

const int size = 200;

class Handle {
    private:
        uint8_t pin;
        int history [size];
        bool sparkActivation;
        bool _isActive;
        unsigned long activationTime;

        void addHistory(int value);
        double historyAvarage();

    public:
        Handle(uint8_t pin);
        bool isActive();
        void update();
};

Handle::Handle(uint8_t pin) {
    this->pin = pin;
    this->_isActive = false;
    this->sparkActivation = false;
    this->activationTime = 0;

    pinMode(this->pin, INPUT_PULLUP);
}

void Handle::update() {
    this->addHistory(digitalRead(this->pin));
    double avg = historyAvarage();
    if (avg >= 0.3 && avg <= 0.7) {
        if (!_isActive) {
            _isActive = true;
            activationTime = millis() + 3 * 1000; // 3 sec;
        }
        
        if (millis () > activationTime) {
            _isActive = false;
            activationTime = 0;
            this->sparkActivation = true;
        }
    } else {
        _isActive = false;
        activationTime = 0;
    }
    delay(10);
}

bool Handle::isActive() {
    if (!this->sparkActivation) {
        return false;
    }
    
    this->sparkActivation = false;
    return true;
}

void Handle::addHistory(int value) {
  for (int i = 1; i < size; i++) {
    this->history[i - 1] = this->history[i];
  }
  this->history[size - 1] = value;
}

double Handle::historyAvarage() {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += this->history[i];
  }

  return sum * 1.0 / size;
}
