#ifndef EARCHER_H
#define EARCHER_H

#include "echaracter.h"

class eArcher : public eCharacter {
public:
    eArcher(eGameBoard& board);

    std::shared_ptr<eTexture>
    getTexture(const eTileSize size) const;
};

#endif // EARCHER_H
