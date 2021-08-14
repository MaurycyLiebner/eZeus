#ifndef ETHREADTILE_H
#define ETHREADTILE_H

#include "ethreadbuilding.h"
#include "ethreadcharacter.h"

#include "../etilebase.h"

class eThreadTile : public eTileBase<eThreadTile> {
public:
    void load(eTile* const src);
    void load(const eThreadTile& src);

    bool walkable() const {
        const auto terr = terrain() & eTerrain::walkable;
        if(!static_cast<bool>(terr)) return false;
        if(underBuilding() && !hasRoad()) return false;
        return true;
    }

    bool hasRoad() const {
        return mUnderBuilding.type() == eBuildingType::road;
    }

    bool underBuilding() const {
        return mUnderBuilding.type() != eBuildingType::none;
    }

    std::vector<eThreadCharacter> mCharacters;
    eThreadBuilding mUnderBuilding;
};

#endif // ETHREADTILE_H
