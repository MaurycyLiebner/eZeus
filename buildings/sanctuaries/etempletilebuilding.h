#ifndef ETEMPLETILEBUILDING_H
#define ETEMPLETILEBUILDING_H

#include "esanctbuilding.h"

class eTempleTileBuilding : public eSanctBuilding {
public:
    eTempleTileBuilding(const int id, eGameBoard& board);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
    std::vector<eOverlay>
        getOverlays(const eTileSize size) const;

    std::shared_ptr<eTexture>
        getTileTexture(const eTileSize size) const;

    int id() const { return mId; }
private:
    const int mId;
};

#endif // ETEMPLETILEBUILDING_H
