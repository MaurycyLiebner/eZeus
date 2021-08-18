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

    for(int i = 0; i < 2; i++) {
        fFire.emplace_back(fRenderer);
    }

    for(int i = 37; i < 63; i++) {
        eTextureLoadingHelpers::loadTex(pathBase, i, fFire[0]);
    }
    for(int i = 63; i < 89; i++) {
        eTextureLoadingHelpers::loadTex(pathBase, i, fFire[1]);
    }
}
