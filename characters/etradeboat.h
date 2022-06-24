#ifndef ETRADEBOAT_H
#define ETRADEBOAT_H

#include "echaracter.h"

class eTradeBoat : public eCharacter {
public:
    eTradeBoat(eGameBoard& board);
    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // ETRADEBOAT_H
