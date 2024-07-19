#include "echaractertextures.h"

#include "espriteloader.h"

#include "spriteData/trireme15.h"
#include "spriteData/trireme30.h"
#include "spriteData/trireme45.h"
#include "spriteData/trireme60.h"

#include "spriteData/enemyBoat15.h"
#include "spriteData/enemyBoat30.h"
#include "spriteData/enemyBoat45.h"
#include "spriteData/enemyBoat60.h"

#include "spriteData/eliteCitizen15.h"
#include "spriteData/eliteCitizen30.h"
#include "spriteData/eliteCitizen45.h"
#include "spriteData/eliteCitizen60.h"

#include "offsets/SprMain.h"

void eCharacterTextures::loadTrireme() {
    if(fTriremeLoaded) return;
    fTriremeLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eTriremeSpriteData15,
                                 eTriremeSpriteData30,
                                 eTriremeSpriteData45,
                                 eTriremeSpriteData60);
    eSpriteLoader loader(fTileH, "trireme", sds,
                         &eSprMainOffset, fRenderer);


    for(int j = 0; j < 8; j++) {
        fTrireme.fSwim.emplace_back(fRenderer);
    }

    for(int i = 6570; i < 6633;) {
        for(int j = 0; j < 8; j++, i += 2) {
            loader.load(6569, i, fTrireme.fSwim[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fTrireme.fDie.emplace_back(fRenderer);
    }

    for(int i = 6633; i < 6729;) {
        for(int j = 0; j < 8; j++, i++) {
            loader.load(6569, i, fTrireme.fDie[j]);
        }
    }

    for(int i = 6729; i < 6737; i++) {
        loader.load(6569, i, fTrireme.fStand);
    }
}

void eCharacterTextures::loadEnemyBoat() {
    if(fEnemyBoatLoaded) return;
    fEnemyBoatLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eEnemyBoatSpriteData15,
                                 eEnemyBoatSpriteData30,
                                 eEnemyBoatSpriteData45,
                                 eEnemyBoatSpriteData60);
    eSpriteLoader loader(fTileH, "enemyBoat", sds,
                         &eSprMainOffset, fRenderer);


    for(int j = 0; j < 8; j++) {
        fEnemyBoat.fSwim.emplace_back(fRenderer);
    }

    for(int i = 4834; i < 4897;) {
        for(int j = 0; j < 8; j++, i += 2) {
            loader.load(4833, i, fEnemyBoat.fSwim[j]);
        }
    }

    for(int j = 0; j < 8; j++) {
        fEnemyBoat.fDie.emplace_back(fRenderer);
    }

    for(int i = 4897; i < 4993;) {
        for(int j = 0; j < 8; j++, i++) {
            loader.load(4833, i, fEnemyBoat.fDie[j]);
        }
    }

    for(int i = 4993; i < 5001; i++) {
        loader.load(4833, i, fEnemyBoat.fStand);
    }
}

void eCharacterTextures::loadEliteCitizen() {
    if(fEliteCitizenLoaded) return;
    fEliteCitizenLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eEliteCitizenSpriteData15,
                                 eEliteCitizenSpriteData30,
                                 eEliteCitizenSpriteData45,
                                 eEliteCitizenSpriteData60);
    eSpriteLoader loader(fTileH, "eliteCitizen", sds,
                         &eSprMainOffset, fRenderer);

    loader.loadSkipFlipped(6201, 6201, 6297, fEliteCitizen.fWalk);

    for(int i = 6297; i < 6305; i++) {
        loader.load(6201, i, fEliteCitizen.fDie);
    }

    loader.loadSkipFlipped(6201, 6305, 6401, fEliteCitizen.fFight);
}
