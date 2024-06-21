#ifndef EFIGHTINGPATROLER_H
#define EFIGHTINGPATROLER_H

#include "echaracter.h"

#include "textures/echaractertextures.h"

class eFightingPatroler : public eCharacter {
public:
    using eCharTexs = eFightingCharacterTextures eCharacterTextures::*;
    eFightingPatroler(eGameBoard& board, const eCharTexs charTexs,
                      const eCharacterType type);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;

    void setCharTexs(const eCharTexs& texs);
private:
    eCharTexs mCharTexs;
};

#endif // EFIGHTINGPATROLER_H
