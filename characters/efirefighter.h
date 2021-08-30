#ifndef EFIREFIGHTER_H
#define EFIREFIGHTER_H

#include "echaracter.h"

#include "textures/echaractertextures.h"

class eFireFighter : public eCharacter {
public:
    using eCharTexs = eFireFighterTextures eCharacterTextures::*;
    eFireFighter(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    const std::vector<eCharacterTextures>& mTextures;
    const eCharTexs mCharTexs;
};

#endif // EFIREFIGHTER_H
