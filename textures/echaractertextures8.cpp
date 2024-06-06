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

#include "spriteData/cattle115.h"
#include "spriteData/cattle130.h"
#include "spriteData/cattle145.h"
#include "spriteData/cattle160.h"

#include "spriteData/cattle215.h"
#include "spriteData/cattle230.h"
#include "spriteData/cattle245.h"
#include "spriteData/cattle260.h"

#include "spriteData/cattle315.h"
#include "spriteData/cattle330.h"
#include "spriteData/cattle345.h"
#include "spriteData/cattle360.h"

#include "spriteData/bull15.h"
#include "spriteData/bull30.h"
#include "spriteData/bull45.h"
#include "spriteData/bull60.h"

#include "spriteData/butcher15.h"
#include "spriteData/butcher30.h"
#include "spriteData/butcher45.h"
#include "spriteData/butcher60.h"

#include "offsets/PoseidonImps.h"

void sLoadCattle(eSpriteLoader& loader,
                 eCattleTextures& cattle,
                 const int first) {
    loader.loadSkipFlipped(first, first, first + 96, cattle.fWalk);
    loader.loadSkipFlipped(first, first + 96, first + 192, cattle.fStand);

    for(int i = first + 192; i < first + 200; i++) {
        loader.load(first, i, cattle.fDie);
    }
};

void eCharacterTextures::loadCattle() {
    if(fCattleLoaded) return;
    fCattleLoaded = true;
    {
        const auto& sds = spriteData(fTileH,
                                     eCattle1SpriteData15,
                                     eCattle1SpriteData30,
                                     eCattle1SpriteData45,
                                     eCattle1SpriteData60);
        eSpriteLoader loader(fTileH, "cattle1", sds,
                             &ePoseidonImpsOffset, fRenderer);

        sLoadCattle(loader, fCattle1, 2290);
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eCattle2SpriteData15,
                                     eCattle2SpriteData30,
                                     eCattle2SpriteData45,
                                     eCattle2SpriteData60);
        eSpriteLoader loader(fTileH, "cattle2", sds,
                             &ePoseidonImpsOffset, fRenderer);

        sLoadCattle(loader, fCattle2, 2490);
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eCattle3SpriteData15,
                                     eCattle3SpriteData30,
                                     eCattle3SpriteData45,
                                     eCattle3SpriteData60);
        eSpriteLoader loader(fTileH, "cattle3", sds,
                             &ePoseidonImpsOffset, fRenderer);

        sLoadCattle(loader, fCattle3, 2690);
    }
}

void eCharacterTextures::loadBull() {
    if(fBullLoaded) return;
    fBullLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eBullSpriteData15,
                                 eBullSpriteData30,
                                 eBullSpriteData45,
                                 eBullSpriteData60);
    eSpriteLoader loader(fTileH, "bull", sds,
                         &ePoseidonImpsOffset, fRenderer);

    loader.loadSkipFlipped(2890, 2890, 2986, fBull.fWalk);
    loader.loadSkipFlipped(2890, 2986, 3082, fBull.fStand);

    for(int i = 3082; i < 3090; i++) {
        loader.load(2890, i, fBull.fDie);
    }
    loader.loadSkipFlipped(2890, 3090, 3442, fBull.fAttack);
}

void eCharacterTextures::loadButcher() {
    if(fButcherLoaded) return;
    fButcherLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eButcherSpriteData15,
                                 eButcherSpriteData30,
                                 eButcherSpriteData45,
                                 eButcherSpriteData60);
    eSpriteLoader loader(fTileH, "butcher", sds,
                         &ePoseidonImpsOffset, fRenderer);

    loader.loadSkipFlipped(2186, 2186, 2282, fButcher.fWalk);

    for(int i = 2282; i < 2290; i++) {
        loader.load(2186, i, fButcher.fDie);
    }
}

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
