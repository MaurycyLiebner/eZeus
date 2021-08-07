#ifndef EFIGHTINGPATROLER_H
#define EFIGHTINGPATROLER_H

#include "echaracter.h"

#include "textures/echaractertextures.h"

enum class eFightingPatrolerAction {
    walk, fight, die
};

class eFightingPatroler : public eCharacter {
public:
    using eCharTexs = eFightingPatrolerTextures eCharacterTextures::*;
    eFightingPatroler(const eCharTexs charTexs);

    eFightingPatrolerAction action() const { return mAction; }
    void setAction(const eFightingPatrolerAction a);

    eTexture getTexture(const eTileSize size) const;
private:
    int mActionStartTime = 0;
    eFightingPatrolerAction mAction{eFightingPatrolerAction::walk};

    const std::vector<eCharacterTextures>& mTextures;
    const eCharTexs mCharTexs;
};

#endif // EFIGHTINGPATROLER_H
