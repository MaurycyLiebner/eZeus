#include "egodtextures.h"

#include "etextureloadinghelpers.h"
#include "offsets/Zeus_Athena.h"
#include "offsets/Zeus_Demeter.h"

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

    loadAthena(baseDir);
    loadDemeter(baseDir);
}

void eGodTextures::loadAthena(const std::string& baseDir) {
    const std::string pathBase{baseDir + "Zeus_Athena/Zeus_Athena_"};

    auto& ath = fAthena;
    for(int j = 0; j < 8; j++) {
        ath.fWalk.emplace_back(fRenderer);
        ath.fFight.emplace_back(fRenderer);
        ath.fBless.emplace_back(fRenderer);
    }

    for(int i = 1; i < 121;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, ath.fWalk[j], eZeus_AthenaOffset);
        }
    }

    for(int i = 121; i < 137; i++) {
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, ath.fDisappear, eZeus_AthenaOffset);
    }

    for(int i = 137; i < 297;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, ath.fFight[j], eZeus_AthenaOffset);
        }
    }

    for(int i = 298; i < 426;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, ath.fBless[j], eZeus_AthenaOffset);
        }
    }
}

void eGodTextures::loadDemeter(const std::string& baseDir) {
    const std::string pathBase{baseDir + "Zeus_Demeter/Zeus_Demeter_"};

    auto& dem = fDemeter;
    for(int j = 0; j < 8; j++) {
        dem.fWalk.emplace_back(fRenderer);
        dem.fFight.emplace_back(fRenderer);
    }

    for(int i = 1; i < 225;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, dem.fWalk[j], eZeus_DemeterOffset);
        }
    }

    for(int i = 225; i < 243; i++) {
        eTextureLoadingHelpers::loadTexWithOffset(
                    pathBase, i, dem.fDisappear, eZeus_DemeterOffset);
    }

    for(int i = 243; i < 507;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, dem.fFight[j], eZeus_DemeterOffset);
        }
    }
}
