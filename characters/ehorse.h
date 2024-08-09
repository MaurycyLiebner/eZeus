#ifndef EHORSE_H
#define EHORSE_H

#include "echaracter.h"

class eHorse : public eCharacter {
public:
    eHorse(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;

    std::shared_ptr<eTexture> getNotRotatedTexture(const eTileSize size) const;
};

#endif // EHORSE_H
