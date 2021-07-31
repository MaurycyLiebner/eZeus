#include "echaractertextures.h"

#include "etextureloadinghelpers.h"

eCharacterTextures::eCharacterTextures(const int tileW, const int tileH,
                                       SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),
    fGymnast(renderer) {

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
            eTextureLoadingHelpers::loadTex(pathBase, i, walk[j]);
        }
    }
    for(int i = 10684; i < 10692; i++) {
        auto& die = fGymnast.fDie;
        eTextureLoadingHelpers::loadTex(pathBase, i, die);
    }
}
