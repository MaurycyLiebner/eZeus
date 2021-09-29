#ifndef ETEMPLEMONUMENTBUILDING_H
#define ETEMPLEMONUMENTBUILDING_H


#include "characters/gods/egod.h"

#include "buildings/ebuilding.h"

class eTempleMonumentBuilding : public eBuilding {
public:
    eTempleMonumentBuilding(const eGodType god,
                            const int id, eGameBoard& board);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
private:
    const eGodType mGod;
    const int mId;
};
#endif // ETEMPLEMONUMENTBUILDING_H
