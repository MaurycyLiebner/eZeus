#include "egodtextures.h"

#include "offsets/Zeus_Aphrodite.h"
#include "offsets/Zeus_Apollo.h"
#include "offsets/Zeus_Ares.h"
#include "offsets/Zeus_Artemis.h"
#include "offsets/Zeus_Athena.h"
#include "offsets/Poseidon_Atlas.h"
#include "offsets/Zeus_Demeter.h"
#include "offsets/Zeus_Dionysus.h"
#include "offsets/Zeus_Hades.h"
#include "offsets/Zeus_Hephaestus.h"
#include "offsets/Poseidon_Hera.h"
#include "offsets/Zeus_Hermes.h"
#include "offsets/Zeus_Poseidon.h"
#include "offsets/Zeus_Zeus.h"

#include "spriteData/aphrodite15.h"
#include "spriteData/aphrodite30.h"
#include "spriteData/aphrodite45.h"
#include "spriteData/aphrodite60.h"

#include "spriteData/apollo15.h"
#include "spriteData/apollo30.h"
#include "spriteData/apollo45.h"
#include "spriteData/apollo60.h"

#include "spriteData/ares15.h"
#include "spriteData/ares30.h"
#include "spriteData/ares45.h"
#include "spriteData/ares60.h"

#include "spriteData/artemis15.h"
#include "spriteData/artemis30.h"
#include "spriteData/artemis45.h"
#include "spriteData/artemis60.h"

#include "spriteData/athena15.h"
#include "spriteData/athena30.h"
#include "spriteData/athena45.h"
#include "spriteData/athena60.h"

#include "spriteData/atlas15.h"
#include "spriteData/atlas30.h"
#include "spriteData/atlas45.h"
#include "spriteData/atlas60.h"

#include "spriteData/demeter15.h"
#include "spriteData/demeter30.h"
#include "spriteData/demeter45.h"
#include "spriteData/demeter60.h"

#include "spriteData/dionysus15.h"
#include "spriteData/dionysus30.h"
#include "spriteData/dionysus45.h"
#include "spriteData/dionysus60.h"

#include "spriteData/hades15.h"
#include "spriteData/hades30.h"
#include "spriteData/hades45.h"
#include "spriteData/hades60.h"

#include "spriteData/hephaestus15.h"
#include "spriteData/hephaestus30.h"
#include "spriteData/hephaestus45.h"
#include "spriteData/hephaestus60.h"

#include "spriteData/hera15.h"
#include "spriteData/hera30.h"
#include "spriteData/hera45.h"
#include "spriteData/hera60.h"

#include "spriteData/hermes15.h"
#include "spriteData/hermes30.h"
#include "spriteData/hermes45.h"
#include "spriteData/hermes60.h"

#include "spriteData/poseidon15.h"
#include "spriteData/poseidon30.h"
#include "spriteData/poseidon45.h"
#include "spriteData/poseidon60.h"

#include "spriteData/zeus15.h"
#include "spriteData/zeus30.h"
#include "spriteData/zeus45.h"
#include "spriteData/zeus60.h"

#include "espriteloader.h"
#include "etextureloader.h"

eGodTextures::eGodTextures(const int tileW, const int tileH,
                           SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),

    fAphrodite(renderer),
    fApollo(renderer),
    fAres(renderer),
    fArtemis(renderer),
    fAthena(renderer),
    fAtlas(renderer),
    fDemeter(renderer),
    fDionysus(renderer),
    fHades(renderer),
    fHephaestus(renderer),
    fHera(renderer),
    fHermes(renderer),
    fPoseidon(renderer),
    fZeus(renderer) {

}

void loadBasicGod(eBasicGodTextures& god,
                  const int w0, const int w1,
                  const int d0, const int d1,
                  const int f0, const int f1,
                  eSpriteLoader& loader) {
    loader.loadSkipFlipped(w0, w0, w1, god.fWalk);
    loader.loadSkipFlipped(w0, f0, f1, god.fFight);

    for(int i = d0; i < d1; i++) {
        loader.load(w0, i, god.fDisappear);
    }
}

void loadExtendedGod(eExtendedGodTextures& god,
                     const int w0, const int w1,
                     const int d0, const int d1,
                     const int f0, const int f1,
                     const int b0, const int b1,
                     eSpriteLoader& loader) {
    loadBasicGod(god, w0, w1, d0, d1, f0, f1, loader);
    loader.loadSkipFlipped(w0, b0, b1, god.fBless);
}

void loadDionysusTextures(eDionysusTextures& god,
                          const int w0, const int w1,
                          const int d0, const int d1,
                          const int f0, const int f1,
                          const int a0, const int a1,
                          eSpriteLoader& loader) {
    loadBasicGod(god, w0, w1, d0, d1, f0, f1, loader);
    for(int i = a0; i < a1; i++) {
        loader.load(w0, i, god.fAppear);
    }
}

void loadHermesTextures(eHermesTextures& god,
                        const int w0, const int w1,
                        const int r0, const int r1,
                        const int f0, const int f1,
                        eSpriteLoader& loader) {
    loadBasicGod(god, w0, w1, 0, 0, f0, f1, loader);
    loader.loadSkipFlipped(w0, r0, r1, god.fRun);
}

void eGodTextures::loadAphrodite() {
    if(fAphroditeLoaded) return;
    fAphroditeLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eAphroditeSpriteData15,
                                 eAphroditeSpriteData30,
                                 eAphroditeSpriteData45,
                                 eAphroditeSpriteData60);
    eSpriteLoader loader(fTileH, "aphrodite", sds,
                         &eZeus_AphroditeOffset, fRenderer);
    loadBasicGod(fAphrodite, 1, 209, 209, 241, 241, 441, loader);
}

void eGodTextures::loadApollo() {
    if(fApolloLoaded) return;
    fApolloLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eApolloSpriteData15,
                                 eApolloSpriteData30,
                                 eApolloSpriteData45,
                                 eApolloSpriteData60);
    eSpriteLoader loader(fTileH, "apollo", sds,
                         &eZeus_ApolloOffset, fRenderer);
    loadExtendedGod(fApollo, 1, 185, 185, 201, 202, 346, 347, 515, loader);
}

void eGodTextures::loadAres() {
    if(fAresLoaded) return;
    fAresLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eAresSpriteData15,
                                 eAresSpriteData30,
                                 eAresSpriteData45,
                                 eAresSpriteData60);
    eSpriteLoader loader(fTileH, "ares", sds,
                         &eZeus_AresOffset, fRenderer);
    loadBasicGod(fAres, 1, 249, 249, 265, 265, 433, loader);
}

void eGodTextures::loadArtemis() {
    if(fArtemisLoaded) return;
    fArtemisLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eArtemisSpriteData15,
                                 eArtemisSpriteData30,
                                 eArtemisSpriteData45,
                                 eArtemisSpriteData60);
    eSpriteLoader loader(fTileH, "artemis", sds,
                         &eZeus_ArtemisOffset, fRenderer);//wdfb
    loadExtendedGod(fArtemis, 1, 105, 105, 122, 122, 266, 267, 403, loader);
}

void eGodTextures::loadAthena() {
    if(fAthenaLoaded) return;
    fAthenaLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eAthenaSpriteData15,
                                 eAthenaSpriteData30,
                                 eAthenaSpriteData45,
                                 eAthenaSpriteData60);
    eSpriteLoader loader(fTileH, "athena", sds,
                         &eZeus_AthenaOffset, fRenderer);
    loadExtendedGod(fAthena, 1, 121, 121, 137, 137, 297, 298, 426, loader);
}

void eGodTextures::loadAtlas() {
    if(fAtlasLoaded) return;
    fAtlasLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eAtlasSpriteData15,
                                 eAtlasSpriteData30,
                                 eAtlasSpriteData45,
                                 eAtlasSpriteData60);
    eSpriteLoader loader(fTileH, "atlas", sds,
                         &ePoseidon_AtlasOffset, fRenderer);
    loadExtendedGod(fAtlas, 1, 161, 161, 195, 195, 355, 356, 604, loader);
}

void eGodTextures::loadDemeter() {
    if(fDemeterLoaded) return;
    fDemeterLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eDemeterSpriteData15,
                                 eDemeterSpriteData30,
                                 eDemeterSpriteData45,
                                 eDemeterSpriteData60);
    eSpriteLoader loader(fTileH, "demeter", sds,
                         &eZeus_DemeterOffset, fRenderer);
    loadBasicGod(fDemeter, 1, 225, 225, 243, 243, 507, loader);
}

void eGodTextures::loadDionysus() {
    if(fDionysusLoaded) return;
    fDionysusLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eDionysusSpriteData15,
                                 eDionysusSpriteData30,
                                 eDionysusSpriteData45,
                                 eDionysusSpriteData60);
    eSpriteLoader loader(fTileH, "dionysus", sds,
                         &eZeus_DionysusOffset, fRenderer);
    loadDionysusTextures(fDionysus, 1, 193, 193, 212, 212, 476, 476, 498, loader);
}

void eGodTextures::loadHades() {
    if(fHadesLoaded) return;
    fHadesLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eHadesSpriteData15,
                                 eHadesSpriteData30,
                                 eHadesSpriteData45,
                                 eHadesSpriteData60);
    eSpriteLoader loader(fTileH, "hades", sds,
                         &eZeus_HadesOffset, fRenderer);
    loadBasicGod(fHades, 1, 185, 185, 217, 217, 345, loader);
}

void eGodTextures::loadHephaestus() {
    if(fHephaestusLoaded) return;
    fHephaestusLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eHephaestusSpriteData15,
                                 eHephaestusSpriteData30,
                                 eHephaestusSpriteData45,
                                 eHephaestusSpriteData60);
    eSpriteLoader loader(fTileH, "hephaestus", sds,
                         &eZeus_HephaestusOffset, fRenderer);
    loadBasicGod(fHephaestus, 1, 137, 137, 171, 171, 307, loader);
}

void eGodTextures::loadHera() {
    if(fHeraLoaded) return;
    fHeraLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eHeraSpriteData15,
                                 eHeraSpriteData30,
                                 eHeraSpriteData45,
                                 eHeraSpriteData60);
    eSpriteLoader loader(fTileH, "hera", sds,
                         &ePoseidon_HeraOffset, fRenderer);
    loadBasicGod(fHera, 1, 177, 177, 208, 208, 456, loader);
}

void eGodTextures::loadHermes() {
    if(fHermesLoaded) return;
    fHermesLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eHermesSpriteData15,
                                 eHermesSpriteData30,
                                 eHermesSpriteData45,
                                 eHermesSpriteData60);
    eSpriteLoader loader(fTileH, "hermes", sds,
                         &eZeus_HermesOffset, fRenderer);
    loadHermesTextures(fHermes, 1, 185, 185, 369, 369, 537, loader);
}

void eGodTextures::loadPoseidon() {
    if(fPoseidonLoaded) return;
    fPoseidonLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 ePoseidonSpriteData15,
                                 ePoseidonSpriteData30,
                                 ePoseidonSpriteData45,
                                 ePoseidonSpriteData60);
    eSpriteLoader loader(fTileH, "poseidon", sds,
                         &eZeus_PoseidonOffset, fRenderer);
    loadBasicGod(fPoseidon, 1, 137, 137, 170, 170, 418, loader);
}

void eGodTextures::loadZeus() {
    if(fZeusLoaded) return;
    fZeusLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eZeusSpriteData15,
                                 eZeusSpriteData30,
                                 eZeusSpriteData45,
                                 eZeusSpriteData60);
    eSpriteLoader loader(fTileH, "zeus", sds,
                         &eZeus_ZeusOffset, fRenderer);
    loadExtendedGod(fZeus, 1, 185, 185, 225, 226, 394, 395, 651, loader);
}

void eBasicGodTextures::load(const std::string& pathBase,
                             const int w0, const int w1,
                             const int d0, const int d1,
                             const int f0, const int f1,
                             const eOffsets& offs,
                             eTextureLoader& texLoader) {
    eTextureClass texClass(pathBase, texLoader, &offs);

    texClass.loadSkipFlipped(fWalk, w0, w1);
    texClass.loadSkipFlipped(fFight, f0, f1);

    for(int i = d0; i < d1; i++) {
        texClass.load(i, fDisappear);
    }
}

void eDionysusTextures::load(const std::string& pathBase,
                             const int w0, const int w1,
                             const int d0, const int d1,
                             const int f0, const int f1,
                             const int a0, const int a1,
                             const eOffsets& offs,
                             eTextureLoader& texLoader) {
    eTextureClass texClass(pathBase, texLoader, &offs);

    eBasicGodTextures::load(pathBase,
                            w0, w1, d0, d1, f0, f1,
                            offs, texLoader);
    for(int i = a0; i < a1; i++) {
        texClass.load(i, fAppear);
    }
}

void eHermesTextures::load(const std::string& pathBase,
                           const int w0, const int w1,
                           const int r0, const int r1,
                           const int f0, const int f1,
                           const eOffsets& offs,
                           eTextureLoader& texLoader) {
    eTextureClass texClass(pathBase, texLoader, &offs);

    eBasicGodTextures::load(pathBase,
                            w0, w1, 0, 0, f0, f1,
                            offs, texLoader);
    texClass.loadSkipFlipped(fRun, r0, r1);
}

void eExtendedGodTextures::load(const std::string& pathBase,
                                const int w0, const int w1,
                                const int d0, const int d1,
                                const int f0, const int f1,
                                const int b0, const int b1,
                                const eOffsets& offs,
                                eTextureLoader& texLoader) {
    eTextureClass texClass(pathBase, texLoader, &offs);

    eBasicGodTextures::load(pathBase,
                            w0, w1, d0, d1, f0, f1,
                            offs, texLoader);

    texClass.loadSkipFlipped(fBless, b0, b1);
}
