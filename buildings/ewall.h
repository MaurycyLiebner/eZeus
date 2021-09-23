#ifndef EWALL_H
#define EWALL_H

#include "ebuilding.h"

class eWall : public eBuilding {
public:
    eWall(eGameBoard& board);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
};

#endif // EWALL_H
