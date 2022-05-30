#ifndef EROCKMISSILE_H
#define EROCKMISSILE_H

#include "emissile.h"

class eRockMissile : public eMissile {
public:
    using eMissile::eMissile;

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // EROCKMISSILE_H
