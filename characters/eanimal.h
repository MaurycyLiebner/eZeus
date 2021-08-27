#ifndef EANIMAL_H
#define EANIMAL_H

#include "echaracter.h"

#include "textures/echaractertextures.h"

class eAnimal : public eCharacter {
public:
    using eCharTexs = eAnimalTextures eCharacterTextures::*;
    eAnimal(eGameBoard& board,
            const eCharTexs charTexs,
            const eCharacterType type);

    void setTextures(const eCharTexs& texs);

    eTexture getTexture(const eTileSize size) const;
private:
    const std::vector<eCharacterTextures>& mTextures;
    eCharTexs mCharTexs;
};

#endif // EANIMAL_H
