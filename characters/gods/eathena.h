#ifndef EATHENA_H
#define EATHENA_H

#include "textures/egodtextures.h"
#include "../echaracter.h"


class eAthena : public eCharacter {
public:
    eAthena(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // EATHENA_H
