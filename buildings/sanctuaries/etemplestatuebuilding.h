#ifndef ETEMPLESTATUEBUILDING_H
#define ETEMPLESTATUEBUILDING_H

#include "characters/gods/egod.h"

#include "esanctbuilding.h"

class eTempleStatueBuilding : public eSanctBuilding {
public:
    eTempleStatueBuilding(eSanctuary* const s, const eGodType god,
                          const int id, eGameBoard& board);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
private:
    const eGodType mGod;
    const int mId;
};

#endif // ETEMPLESTATUEBUILDING_H
