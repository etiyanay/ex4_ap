//
// Created by naama on 01/01/17.
//

#include "Clock.h"

using namespace std;

Clock::Clock(int time) {
    this->time = time;
}
int Clock::timeIs() {
    return this->time;
}
void Clock::advanceTime() {
    this->time +=1;
}