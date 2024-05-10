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

    eTextureCollection fBlessed;
    eTextureCollection fCursed;

    eTextureCollection fRock;
    eTextureCollection fArrow;

    eTextureCollection fBless;
    eTextureCollection fCurse;

    eTextureCollection fPlague;

    eTextureCollection fGodOrangeMissile;
    eTextureCollection fGodBlueArrow;
    eTextureCollection fGodOrangeArrow;
    eTextureCollection fMonsterMissile;
    eTextureCollection fGodBlueMissile;
    eTextureCollection fGodRedMissile;
    eTextureCollection fGodGreenMissile;
    eTextureCollection fGodPinkMissile;
    eTextureCollection fGodPurpleMissile;
};

#endif // EDESTRUCTIONTEXTURES_H
