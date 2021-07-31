#ifndef ECHARACTERTEXTURES_H
#define ECHARACTERTEXTURES_H

#include "etexturecollection.h"

struct eGymnastTextures {
    eGymnastTextures(SDL_Renderer* const renderer) :
        fDie(renderer) {}

    std::vector<eTextureCollection> fWalk;
    eTextureCollection fDie;
};

class eCharacterTextures {
public:
    eCharacterTextures(const int tileW, const int tileH,
                       SDL_Renderer* const renderer);

    void load();

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

    eGymnastTextures fGymnast;
};

#endif // ECHARACTERTEXTURES_H
