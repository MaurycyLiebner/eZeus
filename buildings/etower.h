#ifndef ETOWER_H
#define ETOWER_H

#include "ebuilding.h"

class eTower : public eBuilding {
public:
    eTower(eGameBoard& board);

    std::shared_ptr<eTexture>
    getTexture(const eTileSize size) const;
};

#endif // ETOWER_H
