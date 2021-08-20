#ifndef ETHREADBUILDING_H
#define ETHREADBUILDING_H

#include "buildings/ebuilding.h"

class eThreadBuilding {
public:
    void load(eBuilding* const src);
    eBuildingType type() const { return mType; }

    // data1
    int houseVacancies() const { return mData1; }
    // data1
private:
    int mData1{0};
    eBuildingType mType{eBuildingType::none};
};

#endif // ETHREADBUILDING_H
