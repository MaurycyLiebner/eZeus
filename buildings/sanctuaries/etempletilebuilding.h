#ifndef ETEMPLETILEBUILDING_H
#define ETEMPLETILEBUILDING_H

#include "esanctbuilding.h"

class eTempleTileBuilding : public eSanctBuilding {
public:
    eTempleTileBuilding(eSanctuary* const s,
                        const int id, eGameBoard& board);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
    std::vector<eOverlay>
        getOverlays(const eTileSize size) const;
private:
    const int mId;
};

#endif // ETEMPLETILEBUILDING_H
