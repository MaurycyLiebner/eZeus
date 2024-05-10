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

#include "spriteData/disgruntled15.h"
#include "spriteData/disgruntled30.h"
#include "spriteData/disgruntled45.h"
#include "spriteData/disgruntled60.h"

#include "spriteData/sick15.h"
#include "spriteData/sick30.h"
#include "spriteData/sick45.h"
#include "spriteData/sick60.h"

#include "offsets/Zeus_amazon.h"
#include "offsets/Zeus_AresWarriors.h"
#include "offsets/SprMain.h"

void eCharacterTextures::loadDisgruntled() {
    if(fDisgruntledLoaded) return;
    fDisgruntledLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eDisgruntledSpriteData15,
                                 eDisgruntledSpriteData30,
                                 eDisgruntledSpriteData45,
                                 eDisgruntledSpriteData60);
    eSpriteLoader loader(fTileH, "disgruntled", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(6033, 6033, 6129, fDisgruntled.fWalk);
    loader.loadSkipFlipped(6033, 6129, 6201, fDisgruntled.fFight);

    for(int i = 6129; i < 6137; i++) {
        loader.load(6033, i, fDisgruntled.fDie);
    }
}

void eCharacterTextures::loadSick() {
    if(fSickLoaded) return;
    fSickLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eSickSpriteData15,
                                 eSickSpriteData30,
                                 eSickSpriteData45,
                                 eSickSpriteData60);
    eSpriteLoader loader(fTileH, "sick", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(12232, 12232, 12328, fSick.fWalk);
    loader.loadSkipFlipped(12232, 12336, 12432, fSick.fFight);

    for(int i = 12328; i < 12336; i++) {
        loader.load(12232, i, fSick.fDie);
    }
}

void eCharacterTextures::loadAmazonSpear() {
    if(fAmazonSpearLoaded) return;
    fAmazonSpearLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eAmazonSpearSpriteData15,
                                 eAmazonSpearSpriteData30,
                                 eAmazonSpearSpriteData45,
                                 eAmazonSpearSpriteData60);
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
    fAmazonArcherLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eAmazonArcherSpriteData15,
                                 eAmazonArcherSpriteData30,
                                 eAmazonArcherSpriteData45,
                                 eAmazonArcherSpriteData60);
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
    fAresWarriorLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eAresWarriorSpriteData15,
                                 eAresWarriorSpriteData30,
                                 eAresWarriorSpriteData45,
                                 eAresWarriorSpriteData60);
    eSpriteLoader loader(fTileH, "aresWarrior", sds,
                         &eZeus_AresWarriorsOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 89, fAresWarrior.fWalk);
    loader.loadSkipFlipped(1, 89, 241, fAresWarrior.fDie);
    loader.loadSkipFlipped(1, 241, 401, fAresWarrior.fFight);
}
