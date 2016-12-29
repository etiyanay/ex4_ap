#ifndef AP_EX1_CABFACTORY_H
#define AP_EX1_CABFACTORY_H

enum Manufacturer {HONDA = 'H',SUBARO = 'S',TSELA = 'T',FIAT = 'F'};
enum Color {RED = 'R',BLUE= 'B',GREEN = 'G',PINK = 'P',WHITE = 'W'};
/**
 * this is the class of the abstract class that create the cabs
 */
class CabFactory {
public:
    /**
     * @return new cab
     */
    CabFactory(){};
    /**
     * dtor
     */
    virtual ~CabFactory(){};
    /**
     * @return num of km passed
     */
    virtual double howManyKm() = 0;
    /**
     * @return cab's tariff
     */
    virtual double getTariff() = 0;
    /**
     * @return cab's speed
     */
    virtual int getSpeed() = 0;
    /**
     * @param meters meters passed to update the current km passed
     */
    virtual void updateKm(double meters) =0;
    /**
     * @return the manufacturer
     */
    virtual Manufacturer getManufacturer()=0;
    /**
     * @return cab's color
     */
    virtual Color getColor()=0;
    /**
     * @return the id of the current cab
     */
    virtual int getID()=0;
};


#endif //AP_EX1_CABFACTORY_H
