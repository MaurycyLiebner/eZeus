#include "egodtextures.h"

#include "offsets/Zeus_Athena.h"
#include "offsets/Zeus_Demeter.h"
#include "offsets/Zeus_Hades.h"

#include "etextureloader.h"

eGodTextures::eGodTextures(const int tileW, const int tileH,
                           SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),
    fAthena(renderer),
    fDemeter(renderer),
    fHades(renderer) {

}

void eGodTextures::load() {
    std::string baseDir{"../ZeusTextures/"};
    baseDir += std::to_string(fTileH) + "/";

    eTextureLoader texLoader(fRenderer);
    texLoader.initialize();

    loadAthena(baseDir, texLoader);
    loadDemeter(baseDir, texLoader);

    texLoader.waitUntilFinished();
}

void eGodTextures::loadAthena(const std::string& baseDir,
                              eTextureLoader& texLoader) {
    const std::string pathBase{baseDir + "Zeus_Athena/Zeus_Athena_"};
    fAthena.load(pathBase, 1, 121, 121, 137, 137, 297, 298, 426,
                 eZeus_AthenaOffset, texLoader);
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

void eExtendedGodTextures::load(const std::string& pathBase,
                                const int w0, const int w1,
                                const int d0, const int d1,
                                const int f0, const int f1,
                                const int b0, const int b1,
                                const eOffsets& offs,
                                eTextureLoader& texLoader) {
    eTextureClass texClass(pathBase, texLoader, &offs);

    eBasicGodTextures::load(pathBase, w0, w1, d0, d1, f0, f1, offs, texLoader);
    for(int j = 0; j < 8; j++) {
        fBless.emplace_back(fRenderer);
    }
    for(int i = b0; i < b1;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, fBless[j]);
        }
    }
}

void eGodTextures::loadDemeter(const std::string& baseDir,
                               eTextureLoader& texLoader) {
    const std::string pathBase{baseDir + "Zeus_Demeter/Zeus_Demeter_"};
    fDemeter.load(pathBase, 1, 225, 225, 243, 243, 507,
                  eZeus_DemeterOffset, texLoader);
}

void eGodTextures::loadHades(const std::string& baseDir,
                             eTextureLoader& texLoader) {
    const std::string pathBase{baseDir + "Zeus_Hades/Zeus_Hades_"};
    fHades.load(pathBase, 1, 185, 185, 217, 217, 347,
                eZeus_HadesOffset, texLoader);
}
