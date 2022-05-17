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

    bool resourceHas(const eResourceType type) const;
    bool resourceHasSpace(const eResourceType type) const;

    eResourceType gets() const { return mGet; }
    eResourceType empties() const { return mEmpty; }

    SDL_Rect tileRect() const { return mTileRect; }
private:
    SDL_Rect mTileRect;
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
    std::map<eResourceType, int> mMaxCount;

    eResourceType mGet = eResourceType::none;
    eResourceType mEmpty = eResourceType::none;
    eResourceType mAccepts = eResourceType::none; // includes get
};

#endif // ETHREADBUILDING_H
