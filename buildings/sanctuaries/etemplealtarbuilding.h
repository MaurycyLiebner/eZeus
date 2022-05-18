#ifndef ETEMPLEALTARBUILDING_H
#define ETEMPLEALTARBUILDING_H

#include "esanctbuilding.h"

class eTempleAltarBuilding : public eSanctBuilding {
public:
    eTempleAltarBuilding(eSanctuary* const s, eGameBoard& board);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
};

#endif // ETEMPLEALTARBUILDING_H
