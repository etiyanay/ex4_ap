#include "LuxuryCab.h"

LuxuryCab::LuxuryCab(int id ,Manufacturer manuName, Color currentColor) {
    this->id = id;
    this->speed = 2;
    this->tariff = 2;
    this->numOfkm = 0;
    this->manuName = manuName;
    this->currentColor = currentColor;
}
double LuxuryCab::howManyKm(){
    return numOfkm;
}
double LuxuryCab::getTariff(){
    return tariff;
}
void LuxuryCab::updateKm(double meters) {
    numOfkm = numOfkm + meters/1000;
}
int LuxuryCab::getSpeed() {
    return speed;
}
Manufacturer LuxuryCab::getManufacturer() {
    return manuName;
}
Color LuxuryCab::getColor() {
    return currentColor;
}
int LuxuryCab::getID() {
    return this->id;
}