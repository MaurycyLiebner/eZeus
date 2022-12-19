#include "echaractertextures.h"

#include "espriteloader.h"

#include "offsets/zeus_calydonianboar.h"
#include "offsets/zeus_cerberus.h"
#include "offsets/Poseidon_Chimera.h"
#include "offsets/zeus_cyclops.h"
#include "offsets/zeus_dragon.h"
#include "offsets/Poseidon_Echidna.h"
#include "offsets/Poseidon_Harpie.h"
#include "offsets/zeus_hector.h"

#include "spriteData/calydonianBoar15.h"
#include "spriteData/calydonianBoar30.h"
#include "spriteData/calydonianBoar45.h"
#include "spriteData/calydonianBoar60.h"

#include "spriteData/cerberus15.h"
#include "spriteData/cerberus30.h"
#include "spriteData/cerberus45.h"
#include "spriteData/cerberus60.h"

#include "spriteData/chimera15.h"
#include "spriteData/chimera30.h"
#include "spriteData/chimera45.h"
#include "spriteData/chimera60.h"

#include "spriteData/cyclops15.h"
#include "spriteData/cyclops30.h"
#include "spriteData/cyclops45.h"
#include "spriteData/cyclops60.h"

#include "spriteData/dragon15.h"
#include "spriteData/dragon30.h"
#include "spriteData/dragon45.h"
#include "spriteData/dragon60.h"

#include "spriteData/echidna15.h"
#include "spriteData/echidna30.h"
#include "spriteData/echidna45.h"
#include "spriteData/echidna60.h"

#include "spriteData/harpie15.h"
#include "spriteData/harpie30.h"
#include "spriteData/harpie45.h"
#include "spriteData/harpie60.h"

#include "spriteData/hector15.h"
#include "spriteData/hector30.h"
#include "spriteData/hector45.h"
#include "spriteData/hector60.h"

void eCharacterTextures::loadCalydonianBoar() {
    if(fCalydonianBoarLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eCalydonianBoarSpriteData15,
                                 eCalydonianBoarSpriteData30,
                                 eCalydonianBoarSpriteData45,
                                 eCalydonianBoarSpriteData60);
    fCalydonianBoarLoaded = true;
    eSpriteLoader loader(fTileH, "calydonianBoar", sds,
                         &eZeus_calydonianboarOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 97, fCalydonianBoar.fWalk);
    loader.loadSkipFlipped(1, 97, 201, fCalydonianBoar.fDie);
    loader.loadSkipFlipped(1, 201, 361, fCalydonianBoar.fFight);
    loader.loadSkipFlipped(1, 361, 457, fCalydonianBoar.fFight2);
}

void eCharacterTextures::loadCerberus() {
    if(fCerberusLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eCerberusSpriteData15,
                                 eCerberusSpriteData30,
                                 eCerberusSpriteData45,
                                 eCerberusSpriteData60);
    fCerberusLoaded = true;
    eSpriteLoader loader(fTileH, "cerberus", sds,
                         &eZeus_cerberusOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 185, fCerberus.fWalk);
    loader.loadSkipFlipped(1, 185, 361, fCerberus.fDie);
    loader.loadSkipFlipped(1, 361, 465, fCerberus.fFight);
    loader.loadSkipFlipped(1, 465, 633, fCerberus.fFight2);
}

void eCharacterTextures::loadChimera() {
    if(fChimeraLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eChimeraSpriteData15,
                                 eChimeraSpriteData30,
                                 eChimeraSpriteData45,
                                 eChimeraSpriteData60);
    fChimeraLoaded = true;
    eSpriteLoader loader(fTileH, "chimera", sds,
                         &ePoseidon_ChimeraOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 129, fChimera.fWalk);
    loader.loadSkipFlipped(1, 129, 289, fChimera.fDie);
    loader.loadSkipFlipped(1, 289, 489, fChimera.fFight);
    loader.loadSkipFlipped(1, 489, 641, fChimera.fFight2);
}

void eCharacterTextures::loadCyclops() {
    if(fCyclopsLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eCyclopsSpriteData15,
                                 eCyclopsSpriteData30,
                                 eCyclopsSpriteData45,
                                 eCyclopsSpriteData60);
    fCyclopsLoaded = true;
    eSpriteLoader loader(fTileH, "cyclops", sds,
                         &eZeus_cyclopsOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 129, fCyclops.fWalk);
    loader.loadSkipFlipped(1, 129, 289, fCyclops.fDie);
    loader.loadSkipFlipped(1, 289, 425, fCyclops.fFight);
    loader.loadSkipFlipped(1, 425, 553, fCyclops.fFight2);
}

void eCharacterTextures::loadDragon() {
    if(fDragonLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eDragonSpriteData15,
                                 eDragonSpriteData30,
                                 eDragonSpriteData45,
                                 eDragonSpriteData60);
    fDragonLoaded = true;
    eSpriteLoader loader(fTileH, "dragon", sds,
                         &eZeus_dragonOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 161, fDragon.fWalk);
    loader.loadSkipFlipped(1, 161,409, fDragon.fDie);
    loader.loadSkipFlipped(1, 409, 553, fDragon.fFight);
    loader.loadSkipFlipped(1, 553, 697, fDragon.fFight2);
}

void eCharacterTextures::loadEchidna() {
    if(fEchidnaLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eEchidnaSpriteData15,
                                 eEchidnaSpriteData30,
                                 eEchidnaSpriteData45,
                                 eEchidnaSpriteData60);
    fEchidnaLoaded = true;
    eSpriteLoader loader(fTileH, "echidna", sds,
                         &ePoseidon_EchidnaOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 153, fEchidna.fWalk);
    loader.loadSkipFlipped(1, 153, 345, fEchidna.fDie);
    loader.loadSkipFlipped(1, 345, 513, fEchidna.fFight);
    loader.loadSkipFlipped(1, 513, 649, fEchidna.fFight2);
}

void eCharacterTextures::loadHarpie() {
    if(fHarpieLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eHarpieSpriteData15,
                                 eHarpieSpriteData30,
                                 eHarpieSpriteData45,
                                 eHarpieSpriteData60);
    fHarpieLoaded = true;
    eSpriteLoader loader(fTileH, "harpie", sds,
                         &ePoseidon_HarpieOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 337, fHarpies.fWalk);
    loader.loadSkipFlipped(1, 337, 617, fHarpies.fDie);
    loader.loadSkipFlipped(1, 617, 769, fHarpies.fFight);
    loader.loadSkipFlipped(1, 769, 929, fHarpies.fFight2);
}

void eCharacterTextures::loadHector() {
    if(fHectorLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eHectorSpriteData15,
                                 eHectorSpriteData30,
                                 eHectorSpriteData45,
                                 eHectorSpriteData60);
    fHectorLoaded = true;
    eSpriteLoader loader(fTileH, "hector", sds,
                         &eZeus_hectorOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 121, fHector.fWalk);
    loader.loadSkipFlipped(1, 121, 201, fHector.fDie);
    loader.loadSkipFlipped(1, 201, 329, fHector.fFight);
    loader.loadSkipFlipped(1, 329, 465, fHector.fFight2);
}
