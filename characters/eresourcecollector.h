#ifndef ERESOURCECOLLECTOR_H
#define ERESOURCECOLLECTOR_H

#include "echaracter.h"

#include "textures/echaractertextures.h"


enum class eResourceCollectorAction : int{
    walk, collect, carry, die
};

class eResourceCollector : public eCharacter {
public:
    using eCharTexs = eResourceCollectorTextures eCharacterTextures::*;
    eResourceCollector(eGameBoard& board, const eCharTexs charTexs);

    eTexture getTexture(const eTileSize size) const;

    int collected() const { return mResCollected; }
    void incCollected(const int by = 1) { mResCollected += by; }
private:
    const std::vector<eCharacterTextures>& mTextures;
    const eCharTexs mCharTexs;

    int mResCollected = 0;
};

#endif // ERESOURCECOLLECTOR_H
