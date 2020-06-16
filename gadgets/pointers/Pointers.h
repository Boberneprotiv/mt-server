#include "PointersClient.h"

class Pointers {
    private:
        PointersClient* serialClient;
        int currentRequiredIndex;
        int lastActiveIndex;

        void sendEvent(int handIndex);

    public:
        Pointers(PointersClient* serialClient);
        void update();
};

Pointers::Pointers(PointersClient* serialClient) {
    this->serialClient = serialClient;

    this->lastActiveIndex = -1;
    this->currentRequiredIndex = 0;
}

void Pointers::update() {
    if (this->currentRequiredIndex < 6) {
        int hands [6];
        hands[0] = digitalRead(3);
        hands[1] = digitalRead(4);
        hands[2] = digitalRead(5);
        hands[3] = digitalRead(6);
        hands[4] = digitalRead(7);
        hands[5] = digitalRead(8);
    
        for (int i = 0; i < 6; i++) {
            if (hands[i] != HIGH) {
                continue;
            }
    
            if (this->lastActiveIndex == i) {
                continue;
            }
    
            this->lastActiveIndex = i;
            
            if (this->currentRequiredIndex == i) {
                this->currentRequiredIndex++;
                this->sendEvent(i);
            } else {
                this->serialClient->wrongWay();
            }
        }
    }

    if (this->serialClient->isReset()) {
        this->lastActiveIndex = -1;
        this->currentRequiredIndex = 0;
    }
}

void Pointers::sendEvent(int handIndex) {
    switch (handIndex)
    {
        case 0:
            this->serialClient->beginingOfTime();
            break;
        case 1:
            this->serialClient->spring();
            break;
        case 2:
            this->serialClient->summer();
            break;
        case 3:
            this->serialClient->autumn();
            break;
        case 4:
            this->serialClient->sword();
            break;
        case 5:
            this->serialClient->winterIsComming();
            break;
    }
}

 class PointersOld {
     private:
         uint8_t hand1;
         uint8_t hand2;
         uint8_t hand3;
         uint8_t hand4;
         uint8_t hand5;
         uint8_t hand6;
         bool flag1;
         bool flag2;
         bool flag3;
         bool flag4;
         bool flag5;
         bool flag6;
         bool isLastError;
         PointersClient* serialClient;
     public:
         PointersOld(PointersClient* serialClient);
         void update();
 };
 PointersOld::PointersOld(PointersClient* serialClient) {
     this->serialClient = serialClient;
     this->hand1 = 3;
     this->hand2 = 4;
     this->hand3 = 5;
     this->hand4 = 6;
     this->hand5 = 7;
     this->hand6 = 8;
     this->flag1 = 0;
     this->flag2 = 0;
     this->flag3 = 0;
     this->flag4 = 0;
     this->flag5 = 0;
     this->flag6 = 0;
    
     this->isLastError = false;
 }

 void PointersOld::update() {
     int val1 = digitalRead(hand1);
     int val2 = digitalRead(hand2);
     int val3 = digitalRead(hand3);
     int val4 = digitalRead(hand4);
     int val5 = digitalRead(hand5);
     int val6 = digitalRead(hand6);

     if ((val1 == HIGH) && (!flag1)) { //1 ladoshka
         flag1 = 1;
         flag2 = 0;
         flag3 = 0;
         flag4 = 0;
         flag5 = 0;
         flag6 = 0;
         this->isLastError = false;
         this->serialClient->beginingOfTime();
         //zvuk 1
     }

     if ((val2 == HIGH) && (flag1) && (!flag2)) { //2 ladoshka
         flag2 = 1;
         this->isLastError = false;
         this->serialClient->spring();
         //zvuk 2
     } else if (!isLastError && ((val2 == HIGH) && (!flag1))) { //esli 2 ladoshka bez pervoi ili ne v tom poryadke
         this->isLastError = true;
         this->serialClient->wrongWay();
         flag1 = 0;
         flag2 = 0;
         flag3 = 0;
         flag4 = 0;
         flag5 = 0;
         flag6 = 0;
         //nevernoe dvijenie, zvuk
     }

     if ((val3 == HIGH) && (flag2) && (!flag3)) { //3 ladoshka
         flag1 = 0;
         flag3 = 1;
         this->isLastError = false;
         this->serialClient->summer();
         //zvuk 3
     } else if (!isLastError && ((val3 == HIGH) && (!flag2))) { // esli 3 ladoshka ne v svoem poryadke
         this->isLastError = true;
         this->serialClient->wrongWay();
         flag1 = 0;
         flag2 = 0;
         flag3 = 0;
         flag4 = 0;
         flag5 = 0;
         flag6 = 0;
         //nevernoe dvijenie, zvuk
     }
     if ((val4 == HIGH) && (flag3) && (!flag4)) { //4 ladoshka
         flag2 = 0;
         flag4 = 1;
         this->isLastError = false;
         this->serialClient->autumn();
         //zvuk 4
     } else if (!isLastError && ((val4 == HIGH) && (!flag3))) { // esli 4 ladoshka ne v svoem poryadke
         this->isLastError = true;
         this->serialClient->wrongWay();
         flag1 = 0;
         flag2 = 0;
         flag3 = 0;
         flag4 = 0;
         flag5 = 0;
         flag6 = 0;
         //nevernoe dvijenie, zvuk
     }

     //
     if ((val5 == HIGH) && (flag4) && (!flag5)) { //5 ladoshka
         flag3 = 0;
         flag5 = 1;
         this->isLastError = false;
         this->serialClient->sword();
         //zvuk 5
     } else if (!isLastError && ((val5 == HIGH) && (!flag4))) { // esli 5 ladoshka ne v svoem poryadke
         this->isLastError = true;
         this->serialClient->wrongWay();
         flag1 = 0;
         flag2 = 0;
         flag3 = 0;
         flag4 = 0;
         flag5 = 0;
         flag6 = 0;
         //nevernoe dvijenie, zvuk
     }

     if ((val6 == HIGH) && (flag5) && (!flag6)) { //6 ladoshka
         flag4 = 0;
         flag6 = 1;
         this->isLastError = false;
         this->serialClient->winterIsComming();
         //zvuk 6
         //zadanie vypolneno, otpravit' signal na RS-485
     } else if (!isLastError && ((val6 == HIGH) && (!flag5))) { // esli 5 ladoshka ne v svoem poryadke
         this->isLastError = true;
         this->serialClient->wrongWay();
         flag1 = 0;
         flag2 = 0;
         flag3 = 0;
         flag4 = 0;
         flag5 = 0;
         flag6 = 0;
         //nevernoe dvijenie, zvuk
     }
 }
