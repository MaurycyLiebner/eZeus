#ifndef ETEMPLEBUILDING_H
#define ETEMPLEBUILDING_H

#include "esanctbuilding.h"

class eTempleBuilding : public eSanctBuilding {
public:
    eTempleBuilding(eSanctuary* const s, eGameBoard& board);

    std::shared_ptr<eTexture>
    getTexture(const eTileSize) const
    { return nullptr; }
};

#endif // ETEMPLEBUILDING_H
