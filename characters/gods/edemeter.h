#ifndef EDEMETER_H
#define EDEMETER_H

#include "textures/egodtextures.h"
#include "../echaracter.h"


class eDemeter : public eCharacter {
public:
    eDemeter(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // EDEMETER_H
