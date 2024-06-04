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

#include "textures/espriteloader.h"

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
