#ifndef ETHREADTILE_H
#define ETHREADTILE_H

#include "ethreadbuilding.h"
#include "ethreadcharacter.h"

#include "../etilebase.h"

class eThreadTile : public eTileBase {
public:
    void load(eTile* const src);
    void load(const eThreadTile& src);

    bool walkable() const;
    bool hasRoad() const;
    bool hasCharacter(const eHasChar& func) const;
    eBuildingType underBuildingType() const;
    bool isUnderBuilding() const;

    // data1
    int houseVacancies() const { return mData1; }
    // data1
private:
    int mData1{0}; // house vacancies

    std::vector<eThreadCharacter> mCharacters;
    eThreadBuilding mUnderBuilding;
};

#endif // ETHREADTILE_H
