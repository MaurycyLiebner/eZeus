#ifndef EAVENUE_H
#define EAVENUE_H

#include "ebuilding.h"

class eRoad;

class eAvenue : public eBuilding {
public:
    eAvenue(eGameBoard& board);

    int provide(const eProvide p, const int n);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;

    eTile* road() const;
};

#endif // EAVENUE_H
