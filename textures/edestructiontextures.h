#ifndef EDESTRUCTIONTEXTURES_H
#define EDESTRUCTIONTEXTURES_H

#include "etexturecollection.h"

class eDestructionTextures {
public:
    eDestructionTextures(const int tileW, const int tileH,
                         SDL_Renderer* const renderer);

    void load();

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

    std::vector<eTextureCollection> fFire;
//    std::vector<eTextureCollection> fBigFire;

    eTextureCollection fRock;
    eTextureCollection fArrow;
};

#endif // EDESTRUCTIONTEXTURES_H
