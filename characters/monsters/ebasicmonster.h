#ifndef EBASICMONSTER_H
#define EBASICMONSTER_H

#include "emonster.h"
#include "textures/echaractertextures.h"

class eBasicMonster : public eMonster {
public:
    using eCharTexs = eMonsterTextures eCharacterTextures::*;
    eBasicMonster(eGameBoard& board,
                  const eCharTexs charTexs,
                  const eMonsterType type);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    eCharTexs mCharTexs;
};

#endif // EBASICMONSTER_H
