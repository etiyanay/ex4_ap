#include <iostream>
#include "StandardCab.h"

using namespace std;

StandardCab::StandardCab(int id ,Manufacturer manuName, Color currentColor) {
    this->id = id;
    this->speed = 1;
    this->tariff = 1;
    this->numOfkm = 0;
    this->manuName = manuName;
    this->currentColor = currentColor;
}
double StandardCab::howManyKm(){
    return numOfkm;
}
double StandardCab::getTariff(){
    return tariff;
}
void StandardCab::updateKm(double meters) {
    numOfkm = numOfkm + meters/1000;
}
int StandardCab::getSpeed() {
    return speed;
}
Manufacturer StandardCab::getManufacturer() {
    return manuName;
}
Color StandardCab::getColor() {
    return currentColor;
}
int StandardCab::getID() {
    return this->id;
}