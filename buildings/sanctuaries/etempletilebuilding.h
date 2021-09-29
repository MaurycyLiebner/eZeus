#ifndef ETEMPLETILEBUILDING_H
#define ETEMPLETILEBUILDING_H

#include "../ebuilding.h"

class eTempleTileBuilding : public eBuilding {
public:
    eTempleTileBuilding(const int id, eGameBoard& board);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
    std::vector<eOverlay>
        getOverlays(const eTileSize size) const;
private:
    const int mId;
};

#endif // ETEMPLETILEBUILDING_H
