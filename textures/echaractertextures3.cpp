#include "echaractertextures.h"

#include "espriteloader.h"

#include "offsets/zeus_achilles.h"
#include "offsets/Poseidon_Atalanta.h"
#include "offsets/Poseidon_Bellerophon.h"
#include "offsets/zeus_heracles.h"

#include "spriteData/achilles15.h"
#include "spriteData/achilles30.h"
#include "spriteData/achilles45.h"
#include "spriteData/achilles60.h"

#include "spriteData/atalanta15.h"
#include "spriteData/atalanta30.h"
#include "spriteData/atalanta45.h"
#include "spriteData/atalanta60.h"

#include "spriteData/bellerophon15.h"
#include "spriteData/bellerophon30.h"
#include "spriteData/bellerophon45.h"
#include "spriteData/bellerophon60.h"

#include "spriteData/heracles15.h"
#include "spriteData/heracles30.h"
#include "spriteData/heracles45.h"
#include "spriteData/heracles60.h"

void eCharacterTextures::loadAchilles() {
    if(fAchillesLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eAchillesSpriteData15,
                                 eAchillesSpriteData30,
                                 eAchillesSpriteData45,
                                 eAchillesSpriteData60);
    fAchillesLoaded = true;
    eSpriteLoader loader(fTileH, "achilles", sds,
                         &eZeus_achillesOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 257, fAchilles.fWalk);
    loader.loadSkipFlipped(1, 257, 457, fAchilles.fDie);
    loader.loadSkipFlipped(1, 457, 577, fAchilles.fFight);
}

void eCharacterTextures::loadAtalanta() {
    if(fAtalantaLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eAtalantaSpriteData15,
                                 eAtalantaSpriteData30,
                                 eAtalantaSpriteData45,
                                 eAtalantaSpriteData60);
    fAtalantaLoaded = true;
    eSpriteLoader loader(fTileH, "atalanta", sds,
                         &ePoseidon_AtalantaOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 161, fAtalanta.fWalk);
    loader.loadSkipFlipped(1, 161, 329, fAtalanta.fDie);
    loader.loadSkipFlipped(1, 329, 473, fAtalanta.fFight);
}

void eCharacterTextures::loadBellerophon() {
    if(fBellerophonLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eBellerophonSpriteData15,
                                 eBellerophonSpriteData30,
                                 eBellerophonSpriteData45,
                                 eBellerophonSpriteData60);
    fBellerophonLoaded = true;
    eSpriteLoader loader(fTileH, "bellerophon", sds,
                         &ePoseidon_BellerophonOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 121, fBellerophon.fWalk);
    loader.loadSkipFlipped(1, 121, 289, fBellerophon.fDie);
    loader.loadSkipFlipped(1, 289, 529, fBellerophon.fFight);
}

void eCharacterTextures::loadHeracles() {
    if(fHeraclesLoaded) return;
    const auto& sds = spriteData(fTileH,
                                 eHeraclesSpriteData15,
                                 eHeraclesSpriteData30,
                                 eHeraclesSpriteData45,
                                 eHeraclesSpriteData60);
    fHeraclesLoaded = true;
    eSpriteLoader loader(fTileH, "heracles", sds,
                         &eZeus_heraclesOffset, fRenderer);

    loader.loadSkipFlipped(1, 1, 185, fHercules.fWalk);
    loader.loadSkipFlipped(1, 185, 345, fHercules.fDie);
    loader.loadSkipFlipped(1, 345, 481, fHercules.fFight);
}
