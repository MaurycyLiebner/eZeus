#ifndef EFIGHTINGPATROLER_H
#define EFIGHTINGPATROLER_H

#include "echaracter.h"

#include "textures/echaractertextures.h"

class eFightingPatroler : public eCharacter {
public:
    using eCharTexs = eFightingCharacterTextures eCharacterTextures::*;
    eFightingPatroler(eGameBoard& board, const eCharTexs charTexs,
                      const eCharacterType type);

    eTexture getTexture(const eTileSize size) const;
private:
    const std::vector<eCharacterTextures>& mTextures;
    const eCharTexs mCharTexs;
};

#endif // EFIGHTINGPATROLER_H
