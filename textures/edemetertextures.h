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
    eTextureCollection fDie;
    std::vector<eTextureCollection> fFight;
};

#endif // EDEMETERTEXTURES_H
