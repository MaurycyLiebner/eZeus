#ifndef EANIMAL_H
#define EANIMAL_H

#include "echaracter.h"

#include "textures/echaractertextures.h"

class eAnimal : public eCharacter {
public:
    using eCharTexs = eAnimalTextures eCharacterTextures::*;
    eAnimal(eSpawner* const s,
            eGameBoard& board,
            const eCharTexs charTexs);
    ~eAnimal();

    eTexture getTexture(const eTileSize size) const;
private:
    const std::vector<eCharacterTextures>& mTextures;
    const eCharTexs mCharTexs;
    eSpawner* const mSpawner;
};

#endif // EANIMAL_H
