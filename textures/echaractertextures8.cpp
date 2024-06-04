#include "echaractertextures.h"

#include "espriteloader.h"

#include "spriteData/scholar15.h"
#include "spriteData/scholar30.h"
#include "spriteData/scholar45.h"
#include "spriteData/scholar60.h"

#include "spriteData/astronomer15.h"
#include "spriteData/astronomer30.h"
#include "spriteData/astronomer45.h"
#include "spriteData/astronomer60.h"

#include "spriteData/inventor15.h"
#include "spriteData/inventor30.h"
#include "spriteData/inventor45.h"
#include "spriteData/inventor60.h"

#include "spriteData/curator15.h"
#include "spriteData/curator30.h"
#include "spriteData/curator45.h"
#include "spriteData/curator60.h"

#include "spriteData/hoplitePoseidon15.h"
#include "spriteData/hoplitePoseidon30.h"
#include "spriteData/hoplitePoseidon45.h"
#include "spriteData/hoplitePoseidon60.h"

#include "spriteData/chariotPoseidon15.h"
#include "spriteData/chariotPoseidon30.h"
#include "spriteData/chariotPoseidon45.h"
#include "spriteData/chariotPoseidon60.h"

#include "spriteData/archerPoseidon15.h"
#include "spriteData/archerPoseidon30.h"
#include "spriteData/archerPoseidon45.h"
#include "spriteData/archerPoseidon60.h"

#include "offsets/PoseidonImps.h"

void eCharacterTextures::loadScholar() {
    if(fScholarLoaded) return;
    fScholarLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eScholarSpriteData15,
                                 eScholarSpriteData30,
                                 eScholarSpriteData45,
                                 eScholarSpriteData60);
    eSpriteLoader loader(fTileH, "scholar", sds,
                         &ePoseidonImpsOffset, fRenderer);

    loader.loadSkipFlipped(2082, 2082, 2178, fScholar.fWalk);

    for(int i = 2178; i < 2186; i++) {
        loader.load(2082, i, fScholar.fDie);
    }
}

void eCharacterTextures::loadAstronomer() {
    if(fAstronomerLoaded) return;
    fAstronomerLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eAstronomerSpriteData15,
                                 eAstronomerSpriteData30,
                                 eAstronomerSpriteData45,
                                 eAstronomerSpriteData60);
    eSpriteLoader loader(fTileH, "astronomer", sds,
                         &ePoseidonImpsOffset, fRenderer);

    loader.loadSkipFlipped(79, 79, 175, fAstronomer.fWalk);

    for(int i = 175; i < 183; i++) {
        loader.load(79, i, fAstronomer.fDie);
    }
}

void eCharacterTextures::loadInventor() {
    if(fInventorLoaded) return;
    fInventorLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eInventorSpriteData15,
                                 eInventorSpriteData30,
                                 eInventorSpriteData45,
                                 eInventorSpriteData60);
    eSpriteLoader loader(fTileH, "inventor", sds,
                         &ePoseidonImpsOffset, fRenderer);

    loader.loadSkipFlipped(3442, 3442, 3538, fInventor.fWalk);

    for(int i = 3538; i < 3546; i++) {
        loader.load(3442, i, fInventor.fDie);
    }
}

void eCharacterTextures::loadCurator() {
    if(fCuratorLoaded) return;
    fCuratorLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eCuratorSpriteData15,
                                 eCuratorSpriteData30,
                                 eCuratorSpriteData45,
                                 eCuratorSpriteData60);
    eSpriteLoader loader(fTileH, "curator", sds,
                         &ePoseidonImpsOffset, fRenderer);

    loader.loadSkipFlipped(79, 79, 175, fCurator.fWalk);

    for(int i = 175; i < 183; i++) {
        loader.load(79, i, fCurator.fDie);
    }
}

void eCharacterTextures::loadChariotPoseidon() {
    if(fChariotPoseidonLoaded) return;
    fChariotPoseidonLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eChariotPoseidonSpriteData15,
                                 eChariotPoseidonSpriteData30,
                                 eChariotPoseidonSpriteData45,
                                 eChariotPoseidonSpriteData60);
    eSpriteLoader loader(fTileH, "chariotPoseidon", sds,
                         &ePoseidonImpsOffset, fRenderer);

    loader.loadSkipFlipped(3910, 3910, 4006, fChariotPoseidon.fWalk);
    loader.loadSkipFlipped(3910, 4078, 4174, fChariotPoseidon.fFight);
    loader.loadSkipFlipped(3910, 4006, 4078, fChariotPoseidon.fDie);
}

void eCharacterTextures::loadArcherPoseidon() {
    if(fArcherPoseidonLoaded) return;
    fArcherPoseidonLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eArcherPoseidonSpriteData15,
                                 eArcherPoseidonSpriteData30,
                                 eArcherPoseidonSpriteData45,
                                 eArcherPoseidonSpriteData60);
    eSpriteLoader loader(fTileH, "archerPoseidon", sds,
                         &ePoseidonImpsOffset, fRenderer);

    loader.loadSkipFlipped(4174, 4174, 4270, fArcherPoseidon.fWalk);
    loader.loadSkipFlipped(4174, 4278, 4398, fArcherPoseidon.fFight);

    for(int i = 4270; i < 4278; i++) {
        loader.load(4174, i, fArcherPoseidon.fDie);
    }
}

void eCharacterTextures::loadHoplitePoseidon() {
    if(fHoplitePoseidonLoaded) return;
    fHoplitePoseidonLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eHoplitePoseidonSpriteData15,
                                 eHoplitePoseidonSpriteData30,
                                 eHoplitePoseidonSpriteData45,
                                 eHoplitePoseidonSpriteData60);
    eSpriteLoader loader(fTileH, "hoplitePoseidon", sds,
                         &ePoseidonImpsOffset, fRenderer);

    loader.loadSkipFlipped(3742, 3742, 3838, fHoplitePoseidon.fWalk);
    loader.loadSkipFlipped(3742, 3846, 3910, fHoplitePoseidon.fFight);

    for(int i = 3838; i < 3846; i++) {
        loader.load(3742, i, fHoplitePoseidon.fDie);
    }
}
