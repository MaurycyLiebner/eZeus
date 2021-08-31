#ifndef ETHREADBUILDING_H
#define ETHREADBUILDING_H

#include "buildings/estoragebuilding.h"

class eThreadBuilding {
public:
    void load(eBuilding* const src);
    eBuildingType type() const { return mType; }

    int houseVacancies() const { return mVacancies; }

    bool workedOn() const { return mWorkedOn; }

    int resourceCount(const eResourceType type) const;
    int resourceSpaceLeft(const eResourceType type) const;
private:
    eBuildingType mType{eBuildingType::none};

    int mVacancies{0};

    bool mWorkedOn = false;

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
    std::map<eResourceType, int> mMaxCount;
};

#endif // ETHREADBUILDING_H
