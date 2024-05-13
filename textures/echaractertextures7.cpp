#include "echaractertextures.h"

#include "espriteloader.h"

#include "spriteData/egyptianHoplite15.h"
#include "spriteData/egyptianHoplite30.h"
#include "spriteData/egyptianHoplite45.h"
#include "spriteData/egyptianHoplite60.h"

#include "spriteData/egyptianArcher15.h"
#include "spriteData/egyptianArcher30.h"
#include "spriteData/egyptianArcher45.h"
#include "spriteData/egyptianArcher60.h"

#include "spriteData/egyptianChariot15.h"
#include "spriteData/egyptianChariot30.h"
#include "spriteData/egyptianChariot45.h"
#include "spriteData/egyptianChariot60.h"

#include "spriteData/atlanteanHoplite15.h"
#include "spriteData/atlanteanHoplite30.h"
#include "spriteData/atlanteanHoplite45.h"
#include "spriteData/atlanteanHoplite60.h"

#include "spriteData/atlanteanArcher15.h"
#include "spriteData/atlanteanArcher30.h"
#include "spriteData/atlanteanArcher45.h"
#include "spriteData/atlanteanArcher60.h"

#include "spriteData/atlanteanChariot15.h"
#include "spriteData/atlanteanChariot30.h"
#include "spriteData/atlanteanChariot45.h"
#include "spriteData/atlanteanChariot60.h"

#include "spriteData/mayanHoplite15.h"
#include "spriteData/mayanHoplite30.h"
#include "spriteData/mayanHoplite45.h"
#include "spriteData/mayanHoplite60.h"

#include "spriteData/mayanArcher15.h"
#include "spriteData/mayanArcher30.h"
#include "spriteData/mayanArcher45.h"
#include "spriteData/mayanArcher60.h"

#include "spriteData/oceanidHoplite15.h"
#include "spriteData/oceanidHoplite30.h"
#include "spriteData/oceanidHoplite45.h"
#include "spriteData/oceanidHoplite60.h"

#include "spriteData/oceanidSpearthrower15.h"
#include "spriteData/oceanidSpearthrower30.h"
#include "spriteData/oceanidSpearthrower45.h"
#include "spriteData/oceanidSpearthrower60.h"

#include "spriteData/phoenicianHorseman15.h"
#include "spriteData/phoenicianHorseman30.h"
#include "spriteData/phoenicianHorseman45.h"
#include "spriteData/phoenicianHorseman60.h"

#include "spriteData/phoenicianArcher15.h"
#include "spriteData/phoenicianArcher30.h"
#include "spriteData/phoenicianArcher45.h"
#include "spriteData/phoenicianArcher60.h"

#include "offsets/Poseidon_Egyptian.h"
#include "offsets/Poseidon_Atlantean.h"
#include "offsets/Poseidon_Mayan.h"
#include "offsets/Poseidon_Oceanid.h"
#include "offsets/Poseidon_Phoenician.h"

void eCharacterTextures::loadAtlanteanChariot() {
    if(fAtlanteanChariotLoaded) return;
    fAtlanteanChariotLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eAtlanteanChariotSpriteData15,
                                 eAtlanteanChariotSpriteData30,
                                 eAtlanteanChariotSpriteData45,
                                 eAtlanteanChariotSpriteData60);
    eSpriteLoader loader(fTileH, "atlanteanChariot", sds,
                         &ePoseidon_AtlanteanOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 97, fAtlanteanChariot.fWalk);
    loader.loadSkipFlipped(1, 169, 265, fAtlanteanChariot.fFight);
    loader.loadSkipFlipped(1, 97, 169, fAtlanteanChariot.fDie);
}

void eCharacterTextures::loadAtlanteanArcher() {
    if(fAtlanteanArcherLoaded) return;
    fAtlanteanArcherLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eAtlanteanArcherSpriteData15,
                                 eAtlanteanArcherSpriteData30,
                                 eAtlanteanArcherSpriteData45,
                                 eAtlanteanArcherSpriteData60);
    eSpriteLoader loader(fTileH, "atlanteanArcher", sds,
                         &ePoseidon_AtlanteanOffset, fRenderer);

    loader.loadSkipFlipped(265, 265, 361, fAtlanteanArcher.fWalk);
    loader.loadSkipFlipped(265, 369, 489, fAtlanteanArcher.fFight);

    for(int i = 361; i < 369; i++) {
        loader.load(265, i, fAtlanteanArcher.fDie);
    }
}

void eCharacterTextures::loadAtlanteanHoplite() {
    if(fAtlanteanHopliteLoaded) return;
    fAtlanteanHopliteLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eAtlanteanHopliteSpriteData15,
                                 eAtlanteanHopliteSpriteData30,
                                 eAtlanteanHopliteSpriteData45,
                                 eAtlanteanHopliteSpriteData60);
    eSpriteLoader loader(fTileH, "atlanteanHoplite", sds,
                         &ePoseidon_AtlanteanOffset, fRenderer);

    loader.loadSkipFlipped(489, 489, 585, fAtlanteanHoplite.fWalk);
    loader.loadSkipFlipped(489, 593, 657, fAtlanteanHoplite.fFight);

    for(int i = 585; i < 593; i++) {
        loader.load(489, i, fAtlanteanHoplite.fDie);
    }
}

void eCharacterTextures::loadEgyptianHoplite() {
    if(fEgyptianHopliteLoaded) return;
    fEgyptianHopliteLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eEgyptianHopliteSpriteData15,
                                 eEgyptianHopliteSpriteData30,
                                 eEgyptianHopliteSpriteData45,
                                 eEgyptianHopliteSpriteData60);
    eSpriteLoader loader(fTileH, "egyptianHoplite", sds,
                         &ePoseidon_EgyptianOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 97, fEgyptianHoplite.fWalk);
    loader.loadSkipFlipped(1, 105, 201, fEgyptianHoplite.fFight);

    for(int i = 97; i < 105; i++) {
        loader.load(1, i, fEgyptianHoplite.fDie);
    }
}

void eCharacterTextures::loadEgyptianChariot() {
    if(fEgyptianChariotLoaded) return;
    fEgyptianChariotLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eEgyptianChariotSpriteData15,
                                 eEgyptianChariotSpriteData30,
                                 eEgyptianChariotSpriteData45,
                                 eEgyptianChariotSpriteData60);
    eSpriteLoader loader(fTileH, "egyptianChariot", sds,
                         &ePoseidon_EgyptianOffset, fRenderer);

    loader.loadSkipFlipped(201, 201, 297, fEgyptianChariot.fWalk);
    loader.loadSkipFlipped(201, 369, 465, fEgyptianChariot.fFight);
    loader.loadSkipFlipped(201, 297, 369, fEgyptianChariot.fDie);
}

void eCharacterTextures::loadEgyptianArcher() {
    if(fEgyptianArcherLoaded) return;
    fEgyptianArcherLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eEgyptianArcherSpriteData15,
                                 eEgyptianArcherSpriteData30,
                                 eEgyptianArcherSpriteData45,
                                 eEgyptianArcherSpriteData60);
    eSpriteLoader loader(fTileH, "egyptianArcher", sds,
                         &ePoseidon_EgyptianOffset, fRenderer);

    loader.loadSkipFlipped(465, 465, 561, fEgyptianArcher.fWalk);
    loader.loadSkipFlipped(465, 569, 665, fEgyptianArcher.fFight);

    for(int i = 561; i < 569; i++) {
        loader.load(465, i, fEgyptianArcher.fDie);
    }
}

void eCharacterTextures::loadMayanHoplite() {
    if(fMayanHopliteLoaded) return;
    fMayanHopliteLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eMayanHopliteSpriteData15,
                                 eMayanHopliteSpriteData30,
                                 eMayanHopliteSpriteData45,
                                 eMayanHopliteSpriteData60);
    eSpriteLoader loader(fTileH, "mayanHoplite", sds,
                         &ePoseidon_MayanOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 97, fMayanHoplite.fWalk);
    loader.loadSkipFlipped(1, 105, 201, fMayanHoplite.fFight);

    for(int i = 97; i < 105; i++) {
        loader.load(1, i, fMayanHoplite.fDie);
    }
}

void eCharacterTextures::loadMayanArcher() {
    if(fMayanArcherLoaded) return;
    fMayanArcherLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eMayanArcherSpriteData15,
                                 eMayanArcherSpriteData30,
                                 eMayanArcherSpriteData45,
                                 eMayanArcherSpriteData60);
    eSpriteLoader loader(fTileH, "mayanArcher", sds,
                         &ePoseidon_MayanOffset, fRenderer);

    loader.loadSkipFlipped(201, 201, 297, fMayanArcher.fWalk);
    loader.loadSkipFlipped(201, 305, 401, fMayanArcher.fFight);

    for(int i = 297; i < 305; i++) {
        loader.load(201, i, fMayanArcher.fDie);
    }
}

void eCharacterTextures::loadPhoenicianHorseman() {
    if(fPhoenicianHorsemanLoaded) return;
    fPhoenicianHorsemanLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 ePhoenicianHorsemanSpriteData15,
                                 ePhoenicianHorsemanSpriteData30,
                                 ePhoenicianHorsemanSpriteData45,
                                 ePhoenicianHorsemanSpriteData60);
    eSpriteLoader loader(fTileH, "phoenicianHorseman", sds,
                         &ePoseidon_PhoenicianOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 97, fPhoenicianHorseman.fWalk);
    loader.loadSkipFlipped(1, 105, 201, fPhoenicianHorseman.fFight);

    for(int i = 97; i < 105; i++) {
        loader.load(1, i, fPhoenicianHorseman.fDie);
    }
}

void eCharacterTextures::loadPhoenicianArcher() {
    if(fPhoenicianArcherLoaded) return;
    fPhoenicianArcherLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 ePhoenicianArcherSpriteData15,
                                 ePhoenicianArcherSpriteData30,
                                 ePhoenicianArcherSpriteData45,
                                 ePhoenicianArcherSpriteData60);
    eSpriteLoader loader(fTileH, "phoenicianArcher", sds,
                         &ePoseidon_PhoenicianOffset, fRenderer);

    loader.loadSkipFlipped(201, 201, 297, fPhoenicianArcher.fWalk);
    loader.loadSkipFlipped(201, 305, 401, fPhoenicianArcher.fFight);

    for(int i = 297; i < 305; i++) {
        loader.load(201, i, fPhoenicianArcher.fDie);
    }
}

void eCharacterTextures::loadOceanidHoplite() {
    if(fOceanidHopliteLoaded) return;
    fOceanidHopliteLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eOceanidHopliteSpriteData15,
                                 eOceanidHopliteSpriteData30,
                                 eOceanidHopliteSpriteData45,
                                 eOceanidHopliteSpriteData60);
    eSpriteLoader loader(fTileH, "oceanidHoplite", sds,
                         &ePoseidon_OceanidOffset, fRenderer);

    loader.loadSkipFlipped(201, 201, 297, fOceanidHoplite.fWalk);
    loader.loadSkipFlipped(201, 305, 369, fOceanidHoplite.fFight);

    for(int i = 297; i < 305; i++) {
        loader.load(201, i, fOceanidHoplite.fDie);
    }
}

void eCharacterTextures::loadOceanidSpearthrower() {
    if(fOceanidSpearthrowerLoaded) return;
    fOceanidSpearthrowerLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 eOceanidSpearthrowerSpriteData15,
                                 eOceanidSpearthrowerSpriteData30,
                                 eOceanidSpearthrowerSpriteData45,
                                 eOceanidSpearthrowerSpriteData60);
    eSpriteLoader loader(fTileH, "oceanidSpearthrower", sds,
                         &ePoseidon_OceanidOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 97, fOceanidSpearthrower.fWalk);
    loader.loadSkipFlipped(1, 105, 201, fOceanidSpearthrower.fFight);

    for(int i = 97; i < 105; i++) {
        loader.load(1, i, fOceanidSpearthrower.fDie);
    }
}

