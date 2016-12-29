#include <iostream>
#include "Point.h"

using namespace std;

ostream &operator<<(ostream &os, const Point *point) {
    point->printPoint(os);
    return os;
}
