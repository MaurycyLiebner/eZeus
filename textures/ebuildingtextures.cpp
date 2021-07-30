#include "ebuildingtextures.h"

#include "etextureloadinghelpers.h"

eBuildingTextures::eBuildingTextures(const int tileW, const int tileH,
                                     SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),
    fGymnasiumOverlay(renderer),
    fBeachRoad(renderer),
    fRoad(renderer) {

}

void eBuildingTextures::load() {
    std::string basedir{"../ZeusTextures/"};
    basedir += std::to_string(fTileH) + "/";
    {
        const auto dir = basedir + "Zeus_General/";

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

    {
        const auto dir = basedir + "Zeus_Terrain/";

        const std::string pathBase{dir + "Zeus_Land3_"};

        for(int i = 81; i < 99; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBeachRoad);
        }

        for(int i = 231; i < 302; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fRoad);
        }
    }
}
