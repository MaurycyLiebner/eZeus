#include "echaractertextures.h"

#include "espriteloader.h"

#include "offsets/PoseidonImps.h"

#include "spriteData/deerHunter15.h"
#include "spriteData/deerHunter30.h"
#include "spriteData/deerHunter45.h"
#include "spriteData/deerHunter60.h"

#include "spriteData/deer15.h"
#include "spriteData/deer30.h"
#include "spriteData/deer45.h"
#include "spriteData/deer60.h"

#include "spriteData/orangesCart15.h"
#include "spriteData/orangesCart30.h"
#include "spriteData/orangesCart45.h"
#include "spriteData/orangesCart60.h"

#include "spriteData/orichalcCart15.h"
#include "spriteData/orichalcCart30.h"
#include "spriteData/orichalcCart45.h"
#include "spriteData/orichalcCart60.h"

#include "spriteData/orangeTender15.h"
#include "spriteData/orangeTender30.h"
#include "spriteData/orangeTender45.h"
#include "spriteData/orangeTender60.h"

#include "spriteData/blackMarbleTrailer15.h"
#include "spriteData/blackMarbleTrailer30.h"
#include "spriteData/blackMarbleTrailer45.h"
#include "spriteData/blackMarbleTrailer60.h"

void eCharacterTextures::loadBlackMarbleTrailer() {
    const auto& sds = spriteData(fTileH,
                                 eBlackMarbleTrailerSpriteData15,
                                 eBlackMarbleTrailerSpriteData30,
                                 eBlackMarbleTrailerSpriteData45,
                                 eBlackMarbleTrailerSpriteData60);
    eSpriteLoader loader(fTileH, "blackMarbleTrailer", sds,
                         &ePoseidonImpsOffset, fRenderer);

    const auto loadTrailer =
            [&](const int min, const int max,
                eTextureCollection& coll,
                const int dy) {
        for(int i = min; i < max; i++) {
            const auto& tex = loader.load(1019, i, coll);
            tex->setOffset(tex->offsetX(), tex->offsetY() + dy);
        }
    };

    loadTrailer(1019, 1027, fBlackMarbleBigTrailer, -4);
    loadTrailer(1027, 1035, fBlackMarbleTrailer1, -7);
    loadTrailer(1035, 1043, fBlackMarbleTrailer2, -7);
}

void eCharacterTextures::loadOrangeTender() {
    const auto& sds = spriteData(fTileH,
                                 eOrangeTenderSpriteData15,
                                 eOrangeTenderSpriteData30,
                                 eOrangeTenderSpriteData45,
                                 eOrangeTenderSpriteData60);
    eSpriteLoader loader(fTileH, "orangeTender", sds,
                         &ePoseidonImpsOffset, fRenderer);

    loader.loadSkipFlipped(1211, 1211, 1307, fOrangeTender.fWalk);
    loader.loadSkipFlipped(1211, 1315, 1411, fOrangeTender.fWorkOnTree);
    loader.loadSkipFlipped(1211, 1411, 1507, fOrangeTender.fCollect);

    for(int i = 1307; i < 1315; i++) {
        loader.load(1211, i, fOrangeTender.fDie);
    }
}

void eCharacterTextures::loadOrangesCart() {
    const auto& sds = spriteData(fTileH,
                                 eOrangesCartSpriteData15,
                                 eOrangesCartSpriteData30,
                                 eOrangesCartSpriteData45,
                                 eOrangesCartSpriteData60);
    eSpriteLoader loader(fTileH, "orangesCart", sds,
                         &ePoseidonImpsOffset, fRenderer);

    loader.loadSkipFlipped(1091, 1091, 1115, fOrangesCart);
}

void eCharacterTextures::loadOrichalcCart() {
    const auto& sds = spriteData(fTileH,
                                 eOrichalcCartSpriteData15,
                                 eOrichalcCartSpriteData30,
                                 eOrichalcCartSpriteData45,
                                 eOrichalcCartSpriteData60);
    eSpriteLoader loader(fTileH, "orichalcCart", sds,
                         &ePoseidonImpsOffset, fRenderer);

    loader.loadSkipFlipped(1115, 1115, 1131, fOrichalcCart);
}

void eCharacterTextures::loadDeerHunter() {
    const auto& sds = spriteData(fTileH,
                                 eDeerHunterSpriteData15,
                                 eDeerHunterSpriteData30,
                                 eDeerHunterSpriteData45,
                                 eDeerHunterSpriteData60);

    eSpriteLoader loader(fTileH, "deerHunter", sds,
                         &ePoseidonImpsOffset, fRenderer);
    loader.loadSkipFlipped(183, 183, 279, fDeerHunter.fWalk);
    loader.loadSkipFlipped(183, 287, 407, fDeerHunter.fCollect);
    loader.loadSkipFlipped(183, 435, 531, fDeerHunter.fCarry);

    for(int i = 279; i < 287; i++) {
        loader.load(183, i, fDeerHunter.fDie);
    }
}

void eCharacterTextures::loadDeer() {
    if(fDeerLoaded) return;
    fDeerLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eDeerSpriteData15,
                                 eDeerSpriteData30,
                                 eDeerSpriteData45,
                                 eDeerSpriteData60);
    eSpriteLoader loader(fTileH, "deer", sds,
                         &ePoseidonImpsOffset, fRenderer);
    loader.loadSkipFlipped(531, 531, 627, fDeer.fWalk);
    loader.loadSkipFlipped(531, 635, 859, fDeer.fFight);
    loader.loadSkipFlipped(531, 859, 955, fDeer.fLayDown);

    for(int i = 627; i < 635; i++) {
        loader.load(531, i, fDeer.fDie);
    }
}
