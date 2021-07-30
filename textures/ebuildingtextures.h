#ifndef EBUILDINGTEXTURES_H
#define EBUILDINGTEXTURES_H

#include "etexturecollection.h"

class eBuildingTextures {
public:
    eBuildingTextures(const int tileW, const int tileH,
                     SDL_Renderer* const renderer);

    void load();

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

    std::vector<eTextureCollection> fSmallHouses;
    eTexture fGymnasium;
    eTextureCollection fGymnasiumOverlay;
    eTextureCollection fBeachRoad;
    eTextureCollection fRoad;
};

#endif // EBUILDINGTEXTURES_H
