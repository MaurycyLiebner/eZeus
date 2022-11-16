#ifndef EROCKMISSILE_H
#define EROCKMISSILE_H

#include "emissile.h"

class eRockMissile : public eMissile {
public:
    eRockMissile(eGameBoard& board,
                 const std::vector<ePathPoint>& path = {});

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // EROCKMISSILE_H
