#ifndef EARROWMISSILE_H
#define EARROWMISSILE_H

#include "emissile.h"

class eArrowMissile : public eMissile {
public:
    eArrowMissile(eGameBoard& board,
                  const std::vector<ePathPoint>& path = {});

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // EARROWMISSILE_H
