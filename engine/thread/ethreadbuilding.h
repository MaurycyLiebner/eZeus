#ifndef ETHREADBUILDING_H
#define ETHREADBUILDING_H

#include "buildings/ebuilding.h"

class eThreadBuilding {
public:
    void load(eBuilding* const src);
    eBuildingType type() const { return mType; }
private:
    eBuildingType mType;
};

#endif // ETHREADBUILDING_H
