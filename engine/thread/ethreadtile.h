#ifndef ETHREADTILE_H
#define ETHREADTILE_H

#include "ethreadbuilding.h"
#include "ethreadcharacter.h"

#include "../etilebase.h"

class eThreadTile : public eTileBase {
public:
    void load(eTile* const src);

    bool hasRoad() const;
    bool hasCharacter(const eHasChar& func) const;
    eBuildingType underBuildingType() const;
    const eThreadBuilding& underBuilding() const
    { return mUnderBuilding; }
    bool isUnderBuilding() const;

    int houseVacancies() const;

    bool onFire() const { return mOnFire; }
    void setOnFire(const bool f) { mOnFire = f; }
private:
    bool mOnFire = false;
    std::vector<eThreadCharacter> mCharacters;
    eThreadBuilding mUnderBuilding;
};

#endif // ETHREADTILE_H
