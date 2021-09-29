#ifndef ETEMPLEALTARBUILDING_H
#define ETEMPLEALTARBUILDING_H

#include "../ebuilding.h"

class eTempleAltarBuilding : public eBuilding {
public:
    eTempleAltarBuilding(eGameBoard& board);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
};

#endif // ETEMPLEALTARBUILDING_H
