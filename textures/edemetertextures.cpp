#include "edemetertextures.h"

#include "etextureloadinghelpers.h"
#include "offsets/Zeus_Demeter.h"

eDemeterTextures::eDemeterTextures(const int tileW, const int tileH,
                                   SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer) {

}

void eDemeterTextures::load() {
    std::string dir{"../ZeusTextures/"};
    dir += std::to_string(fTileH) + "/";
    dir += "Zeus_Demeter/";

    const std::string pathBase{dir + "Zeus_Demeter_"};

    for(int j = 0; j < 8; j++) {
        fWalk.emplace_back(fRenderer);
    }

    for(int i = 1; i < 225;) {
        for(int j = 0; j < 8; j++, i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fWalk[j], eZeus_DemeterOffset);
        }
    }
}
