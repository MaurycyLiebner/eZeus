#ifndef EARTISAN_H
#define EARTISAN_H

#include "echaracter.h"

class eArtisan : public eCharacter {
public:
    eArtisan(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // EARTISAN_H
