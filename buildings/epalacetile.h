#ifndef EPALACETILE_H
#define EPALACETILE_H

#include "ebuilding.h"

class ePalaceTile : public eBuilding {
public:
    ePalaceTile(eGameBoard& board, const bool other);

    void erase() {}

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    const bool mOther;
};

#endif // EPALACETILE_H
