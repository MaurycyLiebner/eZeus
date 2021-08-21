#ifndef ETHREADBUILDING_H
#define ETHREADBUILDING_H

#include "buildings/estoragebuilding.h"

class eThreadBuilding {
public:
    void load(eBuilding* const src);
    eBuildingType type() const { return mType; }

    int houseVacancies() const { return mVacancies; }

    int resourceCount(const eResourceType type) const;
    int resourceSpaceLeft(const eResourceType type) const;
private:
    eBuildingType mType{eBuildingType::none};

    int mVacancies{0};

    int mResourceCount[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    eResourceType mResource[8] = {eResourceType::none,
                                  eResourceType::none,
                                  eResourceType::none,
                                  eResourceType::none,
                                  eResourceType::none,
                                  eResourceType::none,
                                  eResourceType::none,
                                  eResourceType::none};

    eResourceType mAccepts = eResourceType::none;
};

#endif // ETHREADBUILDING_H
