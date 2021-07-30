#include "ebuildingtextures.h"

#include "etextureloadinghelpers.h"

eBuildingTextures::eBuildingTextures(const int tileW, const int tileH,
                                     SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),
    fGymnasiumOverlay(renderer) {

}

void eBuildingTextures::load() {
    std::string dir{"../ZeusTextures/"};
    dir += std::to_string(fTileH) + "/";
    dir += "Zeus_General/";

    {
        const std::string pathBase{dir + "Zeus_Housing_"};

        for(int i = 1; i < 15;) {
            auto& coll = fSmallHouses.emplace_back(fRenderer);
            for(int j = 0; j < 2; j++, i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, coll);
            }
        }
    }

    {
        const std::string pathBase{dir + "Zeus_Culture_"};

        fGymnasium.load(fRenderer, pathBase + "00026.png");

        for(int i = 27; i < 59; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGymnasiumOverlay);
        }
    }
}
