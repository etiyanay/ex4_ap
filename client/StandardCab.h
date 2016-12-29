#ifndef AP_EX1_STANDARDCAB_H
#define AP_EX1_STANDARDCAB_H


#include "CabFactory.h"
/**
 * this is the class of the Standard cab- derives from CabFactory
 */
class StandardCab : public CabFactory {
private:
    int id;
    double numOfkm;
    Manufacturer manuName;
    Color currentColor;
    double tariff;
    int speed;
public:
    /**
     * default constructor
     * @return new StandardCab
     */
    StandardCab(){};
    /**
     *constructor
     * @param id the cab's id
     * @param manuName the cab's manufacturer
     * @param currentColor the cab's color
     * @return a new luxury cab
     */
    StandardCab(int id ,Manufacturer manuName, Color currentColor);
    /**
     * dtor
     */
    ~StandardCab(){};
    /**
     * @return num of km passed
     */
    double howManyKm();
    /**
     * @return cab's tariff
     */
    double getTariff();
    /**
     * @return cab's speed- in this case is 2
     */
    int getSpeed();
    /**
     * @param meters meters passed to update the current km passed
     */
    void updateKm(double meters);
    /**
     * @return the manufacturer
     */
    Manufacturer getManufacturer();
    /**
     * @return cab's color
     */
    Color getColor();
    /**
     * @return cab's id
     */
    int getID();
};


#endif //AP_EX1_STANDARDCAB_H