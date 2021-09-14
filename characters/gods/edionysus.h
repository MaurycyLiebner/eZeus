#ifndef EDIONYSUS_H
#define EDIONYSUS_H

#include "egod.h"

class eDionysus : public eGod {
public:
    eDionysus(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // EDIONYSUS_H
