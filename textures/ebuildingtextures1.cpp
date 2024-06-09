#include "ebuildingtextures.h"

#include "spriteData/bibliotheke15.h"
#include "spriteData/bibliotheke30.h"
#include "spriteData/bibliotheke45.h"
#include "spriteData/bibliotheke60.h"

#include "spriteData/observatory15.h"
#include "spriteData/observatory30.h"
#include "spriteData/observatory45.h"
#include "spriteData/observatory60.h"

#include "spriteData/university15.h"
#include "spriteData/university30.h"
#include "spriteData/university45.h"
#include "spriteData/university60.h"

#include "spriteData/laboratory15.h"
#include "spriteData/laboratory30.h"
#include "spriteData/laboratory45.h"
#include "spriteData/laboratory60.h"

#include "spriteData/inventorsWorkshop15.h"
#include "spriteData/inventorsWorkshop30.h"
#include "spriteData/inventorsWorkshop45.h"
#include "spriteData/inventorsWorkshop60.h"

#include "spriteData/museum15.h"
#include "spriteData/museum30.h"
#include "spriteData/museum45.h"
#include "spriteData/museum60.h"

#include "spriteData/corral15.h"
#include "spriteData/corral30.h"
#include "spriteData/corral45.h"
#include "spriteData/corral60.h"

#include "spriteData/corralCattleOverlay15.h"
#include "spriteData/corralCattleOverlay30.h"
#include "spriteData/corralCattleOverlay45.h"
#include "spriteData/corralCattleOverlay60.h"

#include "spriteData/corralProcessingOverlay15.h"
#include "spriteData/corralProcessingOverlay30.h"
#include "spriteData/corralProcessingOverlay45.h"
#include "spriteData/corralProcessingOverlay60.h"

#include "spriteData/chariotFactory15.h"
#include "spriteData/chariotFactory30.h"
#include "spriteData/chariotFactory45.h"
#include "spriteData/chariotFactory60.h"

#include "spriteData/chariotFactoryOverlay115.h"
#include "spriteData/chariotFactoryOverlay130.h"
#include "spriteData/chariotFactoryOverlay145.h"
#include "spriteData/chariotFactoryOverlay160.h"

#include "spriteData/chariotFactoryHorses15.h"
#include "spriteData/chariotFactoryHorses30.h"
#include "spriteData/chariotFactoryHorses45.h"
#include "spriteData/chariotFactoryHorses60.h"

#include "spriteData/poseidonCommonHouse15.h"
#include "spriteData/poseidonCommonHouse30.h"
#include "spriteData/poseidonCommonHouse45.h"
#include "spriteData/poseidonCommonHouse60.h"

#include "spriteData/poseidonEliteHouse15.h"
#include "spriteData/poseidonEliteHouse30.h"
#include "spriteData/poseidonEliteHouse45.h"
#include "spriteData/poseidonEliteHouse60.h"

#include "offsets/PoseidonImps.h"

#include "textures/espriteloader.h"

void eBuildingTextures::loadPoseidonCommonHouse() {
    if(fPoseidonCommonHouseLoaded) return;
    fPoseidonCommonHouseLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 ePoseidonCommonHouseSpriteData15,
                                 ePoseidonCommonHouseSpriteData30,
                                 ePoseidonCommonHouseSpriteData45,
                                 ePoseidonCommonHouseSpriteData60);
    eSpriteLoader loader(fTileH, "poseidonCommonHouse", sds,
                         nullptr, fRenderer);

    for(int i = 1; i < 11;) {
        auto& coll = fPoseidonCommonHouse.emplace_back(fRenderer);
        for(int j = 0; j < 2; j++, i++) {
            loader.load(1, i, coll);
        }
    }
}

void eBuildingTextures::loadPoseidonEliteHouse() {
    if(fPoseidonEliteHouseLoaded) return;
    fPoseidonEliteHouseLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 ePoseidonEliteHouseSpriteData15,
                                 ePoseidonEliteHouseSpriteData30,
                                 ePoseidonEliteHouseSpriteData45,
                                 ePoseidonEliteHouseSpriteData60);
    eSpriteLoader loader(fTileH, "poseidonEliteHouse", sds,
                         nullptr, fRenderer);

    for(int i = 11; i < 41;) {
        auto& coll = fPoseidonEliteHouse.emplace_back(fRenderer);
        for(int j = 0; j < 5; j++, i++) {
            loader.load(11, i, coll);
        }
    }
}

void eBuildingTextures::loadChariotFactory() {
    if(fChariotFactoryLoaded) return;
    fChariotFactoryLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eChariotFactorySpriteData15,
                                     eChariotFactorySpriteData30,
                                     eChariotFactorySpriteData45,
                                     eChariotFactorySpriteData60);
        eSpriteLoader loader(fTileH, "chariotFactory", sds,
                             nullptr, fRenderer);
        fChariotFactory = loader.load(15, 15);

        for(int i = 16; i < 36; i++) {
            loader.load(15, i, fChariotFactoryOverlay);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eChariotFactoryOverlay1SpriteData15,
                                     eChariotFactoryOverlay1SpriteData30,
                                     eChariotFactoryOverlay1SpriteData45,
                                     eChariotFactoryOverlay1SpriteData60);
        eSpriteLoader loader(fTileH, "chariotFactoryOverlay1", sds,
                             &ePoseidonImpsOffset, fRenderer);

        for(int i = 3718; i < 3742; i++) {
            loader.load(3718, i, fChariotFactoryOverlay1);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eChariotFactoryHorsesSpriteData15,
                                     eChariotFactoryHorsesSpriteData30,
                                     eChariotFactoryHorsesSpriteData45,
                                     eChariotFactoryHorsesSpriteData60);
        eSpriteLoader loader(fTileH, "chariotFactoryHorses", sds,
                             &ePoseidonImpsOffset, fRenderer);

        for(int i = 5374; i < 5558;) {
            auto& coll = fChariotFactoryHorses.emplace_back(fRenderer);
            for(int j = 0; j < 46; j++, i++) {
                loader.load(5374, i, coll);
            }
        }
    }
}

void eBuildingTextures::loadBibliotheke() {
    if(fBibliothekeLoaded) return;
    fBibliothekeLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eBibliothekeSpriteData15,
                                 eBibliothekeSpriteData30,
                                 eBibliothekeSpriteData45,
                                 eBibliothekeSpriteData60);
    eSpriteLoader loader(fTileH, "bibliotheke", sds,
                         nullptr, fRenderer);
    fBibliotheke = loader.load(105, 105);

    for(int i = 106; i < 141; i++) {
        loader.load(105, i, fBibliothekeOverlay);
    }
}

void eBuildingTextures::loadObservatory() {
    if(fObservatoryLoaded) return;
    fObservatoryLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eObservatorySpriteData15,
                                 eObservatorySpriteData30,
                                 eObservatorySpriteData45,
                                 eObservatorySpriteData60);
    eSpriteLoader loader(fTileH, "observatory", sds,
                         nullptr, fRenderer);
    fObservatory = loader.load(141, 141);

    for(int i = 142; i < 162; i++) {
        loader.load(141, i, fObservatoryOverlay);
    }
}

void eBuildingTextures::loadUniversity() {
    if(fUniversityLoaded) return;
    fUniversityLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eUniversitySpriteData15,
                                 eUniversitySpriteData30,
                                 eUniversitySpriteData45,
                                 eUniversitySpriteData60);
    eSpriteLoader loader(fTileH, "university", sds,
                         nullptr, fRenderer);
    fUniversity = loader.load(1, 1);

    for(int i = 2; i < 26; i++) {
        loader.load(1, i, fUniversityOverlay);
    }
}

void eBuildingTextures::loadLaboratory() {
    if(fLaboratoryLoaded) return;
    fLaboratoryLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eLaboratorySpriteData15,
                                 eLaboratorySpriteData30,
                                 eLaboratorySpriteData45,
                                 eLaboratorySpriteData60);
    eSpriteLoader loader(fTileH, "laboratory", sds,
                         nullptr, fRenderer);
    fLaboratory = loader.load(26, 26);

    for(int i = 27; i < 67; i++) {
        loader.load(26, i, fLaboratoryOverlay);
    }
}

void eBuildingTextures::loadInventorsWorkshop() {
    if(fInventorsWorkshopLoaded) return;
    fInventorsWorkshopLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eInventorsWorkshopSpriteData15,
                                 eInventorsWorkshopSpriteData30,
                                 eInventorsWorkshopSpriteData45,
                                 eInventorsWorkshopSpriteData60);
    eSpriteLoader loader(fTileH, "inventorsWorkshop", sds,
                         nullptr, fRenderer);
    fInventorsWorkshop = loader.load(67, 67);

    for(int i = 68; i < 105; i++) {
        loader.load(67, i, fInventorsWorkshopOverlay);
    }
}

void eBuildingTextures::loadMuseum() {
    if(fMuseumLoaded) return;
    fMuseumLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eMuseumSpriteData15,
                                 eMuseumSpriteData30,
                                 eMuseumSpriteData45,
                                 eMuseumSpriteData60);
    eSpriteLoader loader(fTileH, "museum", sds,
                         nullptr, fRenderer);
    fMuseum = loader.load(162, 162);

    for(int i = 163; i < 185; i++) {
        loader.load(162, i, fMuseumOverlay);
    }
}

void eBuildingTextures::loadCorral() {
    if(fCorralLoaded) return;
    fCorralLoaded = true;

    {
        const auto& sds = spriteData(fTileH,
                                     eCorralSpriteData15,
                                     eCorralSpriteData30,
                                     eCorralSpriteData45,
                                     eCorralSpriteData60);
        eSpriteLoader loader(fTileH, "corral", sds,
                             nullptr, fRenderer);
        fCorral = loader.load(1, 1);

        for(int i = 2; i < 49; i++) {
            loader.load(1, i, fCorralOverlay);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eCorralCattleOverlaySpriteData15,
                                     eCorralCattleOverlaySpriteData30,
                                     eCorralCattleOverlaySpriteData45,
                                     eCorralCattleOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "corralCattleOverlay", sds,
                             nullptr, fRenderer);

        for(int i = 0, j = 0; i < 3; i++) {
            auto& o = fCorralCattleOverlay.emplace_back(fRenderer);
            for(int k = 0; k < 21; k++, j++) {
                loader.load(1815, 1815 + j, o);
            }
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eCorralProcessingOverlaySpriteData15,
                                     eCorralProcessingOverlaySpriteData30,
                                     eCorralProcessingOverlaySpriteData45,
                                     eCorralProcessingOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "corralProcessingOverlay", sds,
                             nullptr, fRenderer);

        for(int i = 1878; i < 1938; i++) {
            loader.load(1878, i, fCorralProcessingOverlay);
        }
    }
}
