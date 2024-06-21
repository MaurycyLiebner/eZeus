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

#include "spriteData/homeless15.h"
#include "spriteData/homeless30.h"
#include "spriteData/homeless45.h"
#include "spriteData/homeless60.h"

#include "spriteData/trojanHoplite15.h"
#include "spriteData/trojanHoplite30.h"
#include "spriteData/trojanHoplite45.h"
#include "spriteData/trojanHoplite60.h"

#include "spriteData/trojanSpearthrower15.h"
#include "spriteData/trojanSpearthrower30.h"
#include "spriteData/trojanSpearthrower45.h"
#include "spriteData/trojanSpearthrower60.h"

#include "spriteData/trojanHorseman15.h"
#include "spriteData/trojanHorseman30.h"
#include "spriteData/trojanHorseman45.h"
#include "spriteData/trojanHorseman60.h"

#include "spriteData/centaurHorseman15.h"
#include "spriteData/centaurHorseman30.h"
#include "spriteData/centaurHorseman45.h"
#include "spriteData/centaurHorseman60.h"

#include "spriteData/centaurArcher15.h"
#include "spriteData/centaurArcher30.h"
#include "spriteData/centaurArcher45.h"
#include "spriteData/centaurArcher60.h"

#include "spriteData/persianHoplite15.h"
#include "spriteData/persianHoplite30.h"
#include "spriteData/persianHoplite45.h"
#include "spriteData/persianHoplite60.h"

#include "spriteData/persianHorseman15.h"
#include "spriteData/persianHorseman30.h"
#include "spriteData/persianHorseman45.h"
#include "spriteData/persianHorseman60.h"

#include "spriteData/persianArcher15.h"
#include "spriteData/persianArcher30.h"
#include "spriteData/persianArcher45.h"
#include "spriteData/persianArcher60.h"

#include "offsets/Zeus_amazon.h"
#include "offsets/Zeus_AresWarriors.h"
#include "offsets/SprMain.h"
#include "offsets/Zeus_trojan.h"
#include "offsets/Zeus_centaur.h"
#include "offsets/Zeus_persian.h"

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

void eCharacterTextures::loadHomeless() {
    if(fHomelessLoaded) return;
    fHomelessLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eHomelessSpriteData15,
                                 eHomelessSpriteData30,
                                 eHomelessSpriteData45,
                                 eHomelessSpriteData60);
    eSpriteLoader loader(fTileH, "homeless", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(1441, 1441, 1537, fHomeless.fWalk);

    for(int i = 1537; i < 1545; i++) {
        loader.load(1441, i, fHomeless.fDie);
    }
}

void eCharacterTextures::loadPersianHoplite() {
    if(fPersianHopliteLoaded) return;
    fPersianHopliteLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 ePersianHopliteSpriteData15,
                                 ePersianHopliteSpriteData30,
                                 ePersianHopliteSpriteData45,
                                 ePersianHopliteSpriteData60);
    eSpriteLoader loader(fTileH, "persianHoplite", sds,
                         &eZeus_persianOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 121, fPersianHoplite.fWalk);
    loader.loadSkipFlipped(1, 121, 241, fPersianHoplite.fFight);

    for(int i = 241; i < 257; i++) {
        loader.load(1, i, fPersianHoplite.fDie);
    }
}

void eCharacterTextures::loadPersianArcher() {
    if(fPersianArcherLoaded) return;
    fPersianArcherLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 ePersianArcherSpriteData15,
                                 ePersianArcherSpriteData30,
                                 ePersianArcherSpriteData45,
                                 ePersianArcherSpriteData60);
    eSpriteLoader loader(fTileH, "persianArcher", sds,
                         &eZeus_persianOffset, fRenderer);

    loader.loadSkipFlipped(257, 257, 377, fPersianArcher.fWalk);
    loader.loadSkipFlipped(257, 377, 521, fPersianArcher.fFight);

    for(int i = 521; i < 532; i++) {
        loader.load(257, i, fPersianArcher.fDie);
    }
}

void eCharacterTextures::loadPersianHorseman() {
    if(fPersianHorsemanLoaded) return;
    fPersianHorsemanLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 ePersianHorsemanSpriteData15,
                                 ePersianHorsemanSpriteData30,
                                 ePersianHorsemanSpriteData45,
                                 ePersianHorsemanSpriteData60);
    eSpriteLoader loader(fTileH, "persianHorseman", sds,
                         &eZeus_persianOffset, fRenderer);

    loader.loadSkipFlipped(532, 532, 652, fPersianHorseman.fWalk);
    loader.loadSkipFlipped(532, 652, 772, fPersianHorseman.fFight);

    for(int i = 772; i < 787; i++) {
        loader.load(532, i, fPersianHorseman.fDie);
    }
}

void eCharacterTextures::loadTrojanHoplite() {
    if(fTrojanHopliteLoaded) return;
    fTrojanHopliteLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eTrojanHopliteSpriteData15,
                                 eTrojanHopliteSpriteData30,
                                 eTrojanHopliteSpriteData45,
                                 eTrojanHopliteSpriteData60);
    eSpriteLoader loader(fTileH, "trojanHoplite", sds,
                         &eZeus_trojanOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 97, fTrojanHoplite.fWalk);
    loader.loadSkipFlipped(1, 105, 185, fTrojanHoplite.fFight);

    for(int i = 97; i < 105; i++) {
        loader.load(1, i, fTrojanHoplite.fDie);
    }
}

void eCharacterTextures::loadTrojanSpearthrower() {
    if(fTrojanSpearthrowerLoaded) return;
    fTrojanSpearthrowerLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eTrojanSpearthrowerSpriteData15,
                                 eTrojanSpearthrowerSpriteData30,
                                 eTrojanSpearthrowerSpriteData45,
                                 eTrojanSpearthrowerSpriteData60);
    eSpriteLoader loader(fTileH, "trojanSpearthrower", sds,
                         &eZeus_trojanOffset, fRenderer);

    loader.loadSkipFlipped(185, 185, 281, fTrojanSpearthrower.fWalk);
    loader.loadSkipFlipped(185, 289, 369, fTrojanSpearthrower.fFight);

    for(int i = 281; i < 289; i++) {
        loader.load(185, i, fTrojanSpearthrower.fDie);
    }
}

void eCharacterTextures::loadTrojanHorseman() {
    if(fTrojanHorsemanLoaded) return;
    fTrojanHorsemanLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eTrojanHorsemanSpriteData15,
                                 eTrojanHorsemanSpriteData30,
                                 eTrojanHorsemanSpriteData45,
                                 eTrojanHorsemanSpriteData60);
    eSpriteLoader loader(fTileH, "trojanHorseman", sds,
                         &eZeus_trojanOffset, fRenderer);

    loader.loadSkipFlipped(369, 369, 465, fTrojanHorseman.fWalk);
    loader.loadSkipFlipped(369, 473, 569, fTrojanHorseman.fFight);

    for(int i = 465; i < 473; i++) {
        loader.load(369, i, fTrojanHorseman.fDie);
    }
}

void eCharacterTextures::loadCentaurHorseman() {
    if(fCentaurHorsemanLoaded) return;
    fCentaurHorsemanLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eCentaurHorsemanSpriteData15,
                                 eCentaurHorsemanSpriteData30,
                                 eCentaurHorsemanSpriteData45,
                                 eCentaurHorsemanSpriteData60);
    eSpriteLoader loader(fTileH, "centaurHorseman", sds,
                         &eZeus_centaurOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 153, fCentaurHorseman.fWalk);
    loader.loadSkipFlipped(1, 153, 265, fCentaurHorseman.fFight);

    for(int i = 265; i < 280; i++) {
        loader.load(1, i, fCentaurHorseman.fDie);
    }
}

void eCharacterTextures::loadCentaurArcher() {
    if(fCentaurArcherLoaded) return;
    fCentaurArcherLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eCentaurArcherSpriteData15,
                                 eCentaurArcherSpriteData30,
                                 eCentaurArcherSpriteData45,
                                 eCentaurArcherSpriteData60);
    eSpriteLoader loader(fTileH, "centaurArcher", sds,
                         &eZeus_centaurOffset, fRenderer);

    loader.loadSkipFlipped(280, 280, 416, fCentaurArcher.fWalk);
    loader.loadSkipFlipped(280, 416, 536, fCentaurArcher.fFight);

    for(int i = 536; i < 551; i++) {
        loader.load(280, i, fCentaurArcher.fDie);
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
