#ifndef EAVENUE_H
#define EAVENUE_H

#include "ebuilding.h"

class eAvenue : public eBuilding {
public:
    eAvenue(eGameBoard& board);

    int provide(const eProvide p, const int n);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
};

#endif // EAVENUE_H
