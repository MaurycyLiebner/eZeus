#ifndef EHOPLITE_H
#define EHOPLITE_H

#include "echaracter.h"

class eHoplite : public eCharacter {
public:
    eHoplite(eGameBoard& board);

    std::shared_ptr<eTexture>
    getTexture(const eTileSize size) const;
};

#endif // EHOPLITE_H
