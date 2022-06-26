#ifndef EPALACETILE_H
#define EPALACETILE_H

#include "ebuilding.h"

class ePalaceTile : public eBuilding {
public:
    ePalaceTile(eGameBoard& board);

    void erase() {}

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // EPALACETILE_H
