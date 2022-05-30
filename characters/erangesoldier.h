#ifndef ERANGESOLDIER_H
#define ERANGESOLDIER_H

#include "esoldier.h"

class eRangeSoldier : public eSoldier {
public:
    using eCharTexs = eRockThrowerTextures eCharacterTextures::*;
    eRangeSoldier(eGameBoard& board,
                  const eCharTexs charTexs,
                  const eCharacterType type,
                  const int range);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    const eCharTexs mCharTexs;
};

#endif // ERANGESOLDIER_H
