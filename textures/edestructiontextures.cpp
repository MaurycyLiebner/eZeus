#include "edestructiontextures.h"

#include "etextureloadinghelpers.h"

eDestructionTextures::eDestructionTextures(const int tileW, const int tileH,
                                           SDL_Renderer* const renderer) :
      fTileW(tileW), fTileH(tileH),
      fRenderer(renderer) {

}

void eDestructionTextures::load() {
    std::string dir{"../ZeusTextures/"};
    dir += std::to_string(fTileH) + "/";
    dir += "destruction/";
    const std::string pathBase{dir + "destruction_"};

    for(int i = 0; i < 6; i++) {
        fFire.emplace_back(fRenderer);
    }

    for(int i = 37; i < 63; i++) {
        eTextureLoadingHelpers::loadTex(pathBase, i, fFire[0]);
    }
    for(int i = 63; i < 89; i++) {
        eTextureLoadingHelpers::loadTex(pathBase, i, fFire[1]);
    }
    for(int i = 89; i < 115; i++) {
        eTextureLoadingHelpers::loadTex(pathBase, i, fFire[2]);
    }
    for(int i = 115; i < 133; i++) {
        eTextureLoadingHelpers::loadTex(pathBase, i, fFire[3]);
    }
    for(int i = 133; i < 157; i++) {
        eTextureLoadingHelpers::loadTex(pathBase, i, fFire[4]);
    }
    for(int i = 1007; i < 1033; i++) {
        eTextureLoadingHelpers::loadTex(pathBase, i, fFire[5]);
    }

    for(int i = 0; i < 2; i++) {
        fBigFire.emplace_back(fRenderer);
    }

    for(int i = 1033; i < 1059; i++) {
        eTextureLoadingHelpers::loadTex(pathBase, i, fBigFire[0]);
    }
    for(int i = 1059; i < 1085; i++) {
        eTextureLoadingHelpers::loadTex(pathBase, i, fBigFire[1]);
    }
}
