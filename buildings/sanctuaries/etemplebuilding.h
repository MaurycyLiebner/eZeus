#ifndef ETEMPLEBUILDING_H
#define ETEMPLEBUILDING_H

#include "../ebuilding.h"

class eTempleBuilding : public eBuilding {
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
