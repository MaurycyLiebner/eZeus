#include "echaractertextures.h"

#include "espriteloader.h"

#include "offsets/zeus_jason.h"
#include "offsets/zeus_odysseus.h"
#include "offsets/zeus_perseus.h"
#include "offsets/zeus_theseus.h"

#include "spriteData/jason15.h"
#include "spriteData/jason30.h"
#include "spriteData/jason45.h"
#include "spriteData/jason60.h"

#include "spriteData/odysseus15.h"
#include "spriteData/odysseus30.h"
#include "spriteData/odysseus45.h"
#include "spriteData/odysseus60.h"

#include "spriteData/perseus15.h"
#include "spriteData/perseus30.h"
#include "spriteData/perseus45.h"
#include "spriteData/perseus60.h"

#include "spriteData/theseus15.h"
#include "spriteData/theseus30.h"
#include "spriteData/theseus45.h"
#include "spriteData/theseus60.h"

void eCharacterTextures::loadJason() {
    if(fJasonLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eJasonSpriteData15,
                                 eJasonSpriteData30,
                                 eJasonSpriteData45,
                                 eJasonSpriteData60);
    fJasonLoaded = true;
    eSpriteLoader loader(fTileH, "jason", sds,
                         &eZeus_jasonOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 249, fJason.fWalk);
    loader.loadSkipFlipped(1, 249, 409, fJason.fDie);
    loader.loadSkipFlipped(1, 409, 657, fJason.fFight);
}

void eCharacterTextures::loadOdysseus() {
    if(fOdysseusLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eOdysseusSpriteData15,
                                 eOdysseusSpriteData30,
                                 eOdysseusSpriteData45,
                                 eOdysseusSpriteData60);
    fOdysseusLoaded = true;
    eSpriteLoader loader(fTileH, "odysseus", sds,
                         &eZeus_odysseusOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 241, fOdysseus.fWalk);
    loader.loadSkipFlipped(1, 241, 489, fOdysseus.fDie);
    loader.loadSkipFlipped(1, 489, 769, fOdysseus.fFight);
}

void eCharacterTextures::loadPerseus() {
    if(fPerseusLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 ePerseusSpriteData15,
                                 ePerseusSpriteData30,
                                 ePerseusSpriteData45,
                                 ePerseusSpriteData60);
    fPerseusLoaded = true;
    eSpriteLoader loader(fTileH, "perseus", sds,
                         &eZeus_perseusOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 129, fPerseus.fWalk);
    loader.loadSkipFlipped(1, 129, 289, fPerseus.fDie);
    loader.loadSkipFlipped(1, 289, 417, fPerseus.fFight);
}

void eCharacterTextures::loadTheseus() {
    if(fTheseusLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eTheseusSpriteData15,
                                 eTheseusSpriteData30,
                                 eTheseusSpriteData45,
                                 eTheseusSpriteData60);
    fTheseusLoaded = true;
    eSpriteLoader loader(fTileH, "theseus", sds,
                         &eZeus_theseusOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 185, fTheseus.fWalk);
    loader.loadSkipFlipped(1, 185, 409, fTheseus.fDie);
    loader.loadSkipFlipped(1, 409, 585, fTheseus.fFight);
}
