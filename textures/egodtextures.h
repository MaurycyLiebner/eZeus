#ifndef EGODTEXTURES_H
#define EGODTEXTURES_H

#include "etexturecollection.h"

struct eDemeterTextures {
    eDemeterTextures(SDL_Renderer* const renderer) :
        fDisappear(renderer) {};

    std::vector<eTextureCollection> fWalk;
    eTextureCollection fDisappear;
    std::vector<eTextureCollection> fFight;
};

struct eAthenaTextures {
    eAthenaTextures(SDL_Renderer* const renderer) :
        fDisappear(renderer) {};

    std::vector<eTextureCollection> fWalk;
    eTextureCollection fDisappear;
    std::vector<eTextureCollection> fFight;
    std::vector<eTextureCollection> fBless;
};

class eGodTextures {
public:
    eGodTextures(const int tileW, const int tileH,
                 SDL_Renderer* const renderer);

    void load();

    void loadAthena(const std::string& baseDir);
    void loadDemeter(const std::string& baseDir);

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

    eAthenaTextures fAthena;
    eDemeterTextures fDemeter;
};

#endif // EGODTEXTURES_H
