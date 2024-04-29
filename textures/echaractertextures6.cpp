#include "echaractertextures.h"

#include "espriteloader.h"

#include "spriteData/amazonSpear15.h"
#include "spriteData/amazonSpear30.h"
#include "spriteData/amazonSpear45.h"
#include "spriteData/amazonSpear60.h"

#include "spriteData/amazonArcher15.h"
#include "spriteData/amazonArcher30.h"
#include "spriteData/amazonArcher45.h"
#include "spriteData/amazonArcher60.h"

#include "spriteData/aresWarrior15.h"
#include "spriteData/aresWarrior30.h"
#include "spriteData/aresWarrior45.h"
#include "spriteData/aresWarrior60.h"

#include "offsets/Zeus_amazon.h"
#include "offsets/Zeus_AresWarriors.h"

void eCharacterTextures::loadAmazonSpear() {
    if(fAmazonSpearLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eAmazonSpearSpriteData15,
                                 eAmazonSpearSpriteData30,
                                 eAmazonSpearSpriteData45,
                                 eAmazonSpearSpriteData60);
    fAmazonSpearLoaded = true;
    eSpriteLoader loader(fTileH, "amazonSpear", sds,
                         &eZeus_amazonOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 121, fAmazonSpear.fWalk);
    loader.loadSkipFlipped(1, 121, 241, fAmazonSpear.fFight);

    for(int i = 241; i < 261; i++) {
        loader.load(1, i, fAmazonSpear.fDie);
    }
}

void eCharacterTextures::loadAmazonArcher() {
    if(fAmazonArcherLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eAmazonArcherSpriteData15,
                                 eAmazonArcherSpriteData30,
                                 eAmazonArcherSpriteData45,
                                 eAmazonArcherSpriteData60);
    fAmazonArcherLoaded = true;
    eSpriteLoader loader(fTileH, "amazonArcher", sds,
                         &eZeus_amazonOffset, fRenderer);

    loader.loadSkipFlipped(261, 261, 381, fAmazonArcher.fWalk);
    loader.loadSkipFlipped(261, 121, 525, fAmazonArcher.fFight);

    for(int i = 525; i < 540; i++) {
        loader.load(261, i, fAmazonArcher.fDie);
    }
}

void eCharacterTextures::loadAresWarrior() {
    if(fAresWarriorLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eAresWarriorSpriteData15,
                                 eAresWarriorSpriteData30,
                                 eAresWarriorSpriteData45,
                                 eAresWarriorSpriteData60);
    fAresWarriorLoaded = true;
    eSpriteLoader loader(fTileH, "aresWarrior", sds,
                         &eZeus_AresWarriorsOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 89, fAresWarrior.fWalk);
    loader.loadSkipFlipped(1, 89, 241, fAresWarrior.fDie);
    loader.loadSkipFlipped(1, 241, 401, fAresWarrior.fFight);
}
