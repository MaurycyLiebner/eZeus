#ifndef ECHARACTERTEXTURES_H
#define ECHARACTERTEXTURES_H

#include "etexturecollection.h"

struct eBasicPatrolerTextures {
    eBasicPatrolerTextures(SDL_Renderer* const renderer) :
        fDie(renderer) {}

    std::vector<eTextureCollection> fWalk;
    eTextureCollection fDie;
};

struct eFightingPatrolerTextures : public eBasicPatrolerTextures {
    eFightingPatrolerTextures(SDL_Renderer* const renderer) :
        eBasicPatrolerTextures(renderer) {}

    std::vector<eTextureCollection> fFight;
};

class eCharacterTextures {
public:
    eCharacterTextures(const int tileW, const int tileH,
                       SDL_Renderer* const renderer);

    void load();

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

    eBasicPatrolerTextures fFoodDistributor;
    eBasicPatrolerTextures fActor;
    eBasicPatrolerTextures fTaxCollector;
    eBasicPatrolerTextures fWaterDistributor;
    eFightingPatrolerTextures fWatchman;
    eBasicPatrolerTextures fHealer;
    eBasicPatrolerTextures fGymnast;
    eBasicPatrolerTextures fPhilosopher;
};

#endif // ECHARACTERTEXTURES_H
