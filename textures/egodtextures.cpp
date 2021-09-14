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

void eGodTextures::load() {
    std::string baseDir{"../ZeusTextures/"};
    baseDir += std::to_string(fTileH) + "/";

    eTextureLoader texLoader(fRenderer);
    texLoader.initialize();


    fAphrodite.load(baseDir + "Zeus_Aphrodite/Zeus_Aphrodite_",
                    1, 209, 209, 241, 241, 441,
                    eZeus_AphroditeOffset, texLoader);

    fApollo.load(baseDir + "Zeus_Apollo/Zeus_Apollo_",
                 1, 186, 186, 201, 202, 346, 347, 515,
                 eZeus_ApolloOffset, texLoader);

    fAres.load(baseDir + "Zeus_Ares/Zeus_Ares_",
               1, 249, 249, 265, 265, 433,
               eZeus_AresOffset, texLoader);

    fArtemis.load(baseDir + "Zeus_Artemis/Zeus_Artemis_",
                  1, 105, 105, 122, 122, 266, 267, 403,
                  eZeus_ArtemisOffset, texLoader);

    fAthena.load(baseDir + "Zeus_Athena/Zeus_Athena_",
                 1, 121, 121, 137, 137, 297, 298, 426,
                 eZeus_AthenaOffset, texLoader);

    fAtlas.load(baseDir + "Poseidon_Atlas/Poseidon_Atlas_",
                1, 161, 161, 195, 195, 355, 356, 604,
                ePoseidon_AtlasOffset, texLoader);

    fDemeter.load(baseDir + "Zeus_Demeter/Zeus_Demeter_",
                  1, 225, 225, 243, 243, 507,
                  eZeus_DemeterOffset, texLoader);

    fDionysus.load(baseDir + "Zeus_Dionysus/Zeus_Dionysus_",
                   1, 193, 193, 212, 212, 476, 476, 498,
                   eZeus_DionysusOffset, texLoader);

    fHades.load(baseDir + "Zeus_Hades/Zeus_Hades_",
                1, 185, 185, 217, 217, 345,
                eZeus_HadesOffset, texLoader);

    fHephaestus.load(baseDir + "Zeus_Hephaestus/Zeus_Hephaestus_",
                1, 137, 137, 171, 171, 307,
                eZeus_HephaestusOffset, texLoader);

    fHera.load(baseDir + "Poseidon_Hera/Poseidon_Hera_",
               1, 177, 177, 208, 208, 456,
               ePoseidon_HeraOffset, texLoader);

    fHermes.load(baseDir + "Zeus_Hermes/Zeus_Hermes_",
                 1, 185, 185, 369, 369, 537,
                 eZeus_HermesOffset, texLoader);

    fPoseidon.load(baseDir + "Zeus_Poseidon/Zeus_Poseidon_",
                   1, 137, 137, 170, 170, 418,
                   eZeus_PoseidonOffset, texLoader);

    fZeus.load(baseDir + "Zeus_Zeus/Zeus_Zeus_",
                1, 185, 185, 225, 226, 394, 395, 651,
                eZeus_ZeusOffset, texLoader);

    texLoader.waitUntilFinished();
}

void eBasicGodTextures::load(const std::string& pathBase,
                             const int w0, const int w1,
                             const int d0, const int d1,
                             const int f0, const int f1,
                             const eOffsets& offs,
                             eTextureLoader& texLoader) {
    eTextureClass texClass(pathBase, texLoader, &offs);

    for(int j = 0; j < 8; j++) {
        fWalk.emplace_back(fRenderer);
        fFight.emplace_back(fRenderer);
    }

    for(int i = w0; i < w1;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fWalk[j]);
        }
    }

    for(int i = d0; i < d1; i++) {
        texClass.load(i, fDisappear);
    }

    for(int i = f0; i < f1;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fFight[j]);
        }
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
    for(int j = 0; j < 8; j++) {
        fBless.emplace_back(fRenderer);
    }
    for(int i = b0; i < b1;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fBless[j]);
        }
    }
}
