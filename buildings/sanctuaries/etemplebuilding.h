#ifndef ETEMPLEBUILDING_H
#define ETEMPLEBUILDING_H

#include "esanctbuilding.h"

class eTempleBuilding : public eSanctBuilding {
public:
    eTempleBuilding(const int id, eGameBoard& board);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
    std::vector<eOverlay>
        getOverlays(const eTileSize size) const;
private:
    const int mId;
};

#endif // ETEMPLEBUILDING_H
