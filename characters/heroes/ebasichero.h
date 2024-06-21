#ifndef EBASICHERO_H
#define EBASICHERO_H

#include "ehero.h"
#include "textures/echaractertextures.h"

class eBasicHero : public eHero {
public:
    using eCharTexs = eHeroTextures eCharacterTextures::*;
    eBasicHero(eGameBoard& board,
               const eCharTexs charTexs,
               const eHeroType type);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    eCharTexs mCharTexs;
};

#endif // EBASICHERO_H
