#include "echaractertextures.h"

#include "etextureloadinghelpers.h"
#include "offsets/SprMain.h"

eCharacterTextures::eCharacterTextures(const int tileW, const int tileH,
                                       SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),
    fGymnast(renderer),
    fTaxCollector(renderer),
    fWaterDistributor(renderer),
    fPhilosopher(renderer) {

}

void eCharacterTextures::load() {
    std::string dir{"../ZeusTextures/"};
    dir += std::to_string(fTileH) + "/";
    dir += "SprMain/";

    const std::string pathBase{dir + "SprMain_"};

    for(int j = 0; j < 8; j++) {
        fGymnast.fWalk.emplace_back(fRenderer);
    }

    for(int i = 10588; i < 10684;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fGymnast.fWalk;
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, walk[j], eSprMainOffset);
        }
    }
    for(int i = 10684; i < 10692; i++) {
        auto& die = fGymnast.fDie;
        eTextureLoadingHelpers::loadTex(pathBase, i, die);
    }


    for(int j = 0; j < 8; j++) {
        fTaxCollector.fWalk.emplace_back(fRenderer);
    }

    for(int i = 4625; i < 4721;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fTaxCollector.fWalk;
            eTextureLoadingHelpers::loadTex(pathBase, i, walk[j]);
        }
    }
    for(int i = 4721; i < 4729; i++) {
        auto& die = fTaxCollector.fDie;
        eTextureLoadingHelpers::loadTex(pathBase, i, die);
    }


    for(int j = 0; j < 8; j++) {
        fWaterDistributor.fWalk.emplace_back(fRenderer);
    }

    for(int i = 6737; i < 6833;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fWaterDistributor.fWalk;
            eTextureLoadingHelpers::loadTex(pathBase, i, walk[j]);
        }
    }
    for(int i = 6833; i < 6841; i++) {
        auto& die = fWaterDistributor.fDie;
        eTextureLoadingHelpers::loadTex(pathBase, i, die);
    }

    for(int j = 0; j < 8; j++) {
        fPhilosopher.fWalk.emplace_back(fRenderer);
    }

    for(int i = 12128; i < 12224;) {
        for(int j = 0; j < 8; j++, i++) {
            auto& walk = fPhilosopher.fWalk;
            eTextureLoadingHelpers::loadTex(pathBase, i, walk[j]);
        }
    }
    for(int i = 12224; i < 12232; i++) {
        auto& die = fPhilosopher.fDie;
        eTextureLoadingHelpers::loadTex(pathBase, i, die);
    }
}
