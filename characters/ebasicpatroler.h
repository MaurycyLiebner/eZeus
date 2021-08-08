#ifndef EBASICPATROLER_H
#define EBASICPATROLER_H

#include "echaracter.h"

#include "textures/echaractertextures.h"

enum class eBasicPatrolerAction {
    walk, die
};

class eBasicPatroler : public eCharacter {
public:
    using eCharTexs = eBasicPatrolerTextures eCharacterTextures::*;
    eBasicPatroler(eGameBoard& board, const eCharTexs charTexs);

    eBasicPatrolerAction action() const { return mAction; }
    void setAction(const eBasicPatrolerAction a);

    eTexture getTexture(const eTileSize size) const;
private:
    int mActionStartTime = 0;
    eBasicPatrolerAction mAction{eBasicPatrolerAction::walk};

    const std::vector<eCharacterTextures>& mTextures;
    const eCharTexs mCharTexs;
};

#endif // EBASICPATROLER_H
