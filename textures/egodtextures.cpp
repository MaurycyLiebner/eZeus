#include "egodtextures.h"

#include "etextureloadinghelpers.h"
#include "offsets/Zeus_Athena.h"
#include "offsets/Zeus_Demeter.h"

#include "etextureloader.h"

eGodTextures::eGodTextures(const int tileW, const int tileH,
                           SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),
    fAthena(renderer),
    fDemeter(renderer) {

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

    eTextureClass texClass(pathBase, texLoader, &eZeus_AthenaOffset);

    auto& ath = fAthena;
    for(int j = 0; j < 8; j++) {
        ath.fWalk.emplace_back(fRenderer);
        ath.fFight.emplace_back(fRenderer);
        ath.fBless.emplace_back(fRenderer);
    }

    for(int i = 1; i < 121;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, ath.fWalk[j]);
        }
    }

    for(int i = 121; i < 137; i++) {
        texClass.load(i, ath.fDisappear);
    }

    for(int i = 137; i < 297;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, ath.fFight[j]);
        }
    }

    for(int i = 298; i < 426;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, ath.fBless[j]);
        }
    }
}

void eGodTextures::loadDemeter(const std::string& baseDir,
                               eTextureLoader& texLoader) {
    const std::string pathBase{baseDir + "Zeus_Demeter/Zeus_Demeter_"};

    eTextureClass texClass(pathBase, texLoader, &eZeus_DemeterOffset);

    auto& dem = fDemeter;
    for(int j = 0; j < 8; j++) {
        dem.fWalk.emplace_back(fRenderer);
        dem.fFight.emplace_back(fRenderer);
    }

    for(int i = 1; i < 225;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, dem.fWalk[j]);
        }
    }

    for(int i = 225; i < 243; i++) {
        texClass.load(i, dem.fDisappear);
    }

    for(int i = 243; i < 507;) {
        for(int j = 0; j < 8; j++, i++) {
            texClass.load(i, dem.fFight[j]);
        }
    }
}
