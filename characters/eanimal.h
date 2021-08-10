#ifndef EANIMAL_H
#define EANIMAL_H

#include "echaracter.h"

#include "textures/echaractertextures.h"

enum class eAnimalAction {
    walk, fight, die
};

class eAnimal : public eCharacter {
public:
    using eCharTexs = eAnimalTextures eCharacterTextures::*;
    eAnimal(eSpawner* const s,
            eGameBoard& board,
            const eCharTexs charTexs);
    ~eAnimal();

    eAnimalAction action() const { return mAction; }
    void setAction(const eAnimalAction a);

    eTexture getTexture(const eTileSize size) const;
private:
    int mActionStartTime = 0;
    eAnimalAction mAction{eAnimalAction::walk};

    const std::vector<eCharacterTextures>& mTextures;
    const eCharTexs mCharTexs;
    eSpawner* const mSpawner;
};

#endif // EANIMAL_H
