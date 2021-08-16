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
    bool underBuilding() const;
private:
    std::vector<eThreadCharacter> mCharacters;
    eThreadBuilding mUnderBuilding;
};

#endif // ETHREADTILE_H
