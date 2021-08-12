#ifndef EBASICPATROLER_H
#define EBASICPATROLER_H

#include "echaracter.h"

#include "textures/echaractertextures.h"

class eBasicPatroler : public eCharacter {
public:
    using eCharTexs = eBasicPatrolerTextures eCharacterTextures::*;
    eBasicPatroler(eGameBoard& board, const eCharTexs charTexs);

    eTexture getTexture(const eTileSize size) const;
private:
    const std::vector<eCharacterTextures>& mTextures;
    const eCharTexs mCharTexs;
};

#endif // EBASICPATROLER_H
