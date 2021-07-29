#ifndef EDEMETERTEXTURES_H
#define EDEMETERTEXTURES_H

#include "etexturecollection.h"

class eDemeterTextures {
public:
    eDemeterTextures(const int tileW, const int tileH,
                     SDL_Renderer* const renderer);

    void load();

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

    std::vector<eTextureCollection> fWalk;
};

#endif // EDEMETERTEXTURES_H
