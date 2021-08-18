#ifndef ECHARACTERTEXTURES_H
#define ECHARACTERTEXTURES_H

#include "etexturecollection.h"

struct eBasicCharacterTextures {
    eBasicCharacterTextures(SDL_Renderer* const renderer) :
        fDie(renderer) {}

    std::vector<eTextureCollection> fWalk;
    eTextureCollection fDie;
};

struct eResourceCollectorTextures : public eBasicCharacterTextures {
    eResourceCollectorTextures(SDL_Renderer* const renderer) :
        eBasicCharacterTextures(renderer) {}

    std::vector<eTextureCollection> fCarry;
    std::vector<eTextureCollection> fCollect;
};


struct eFightingCharacterTextures : public eBasicCharacterTextures {
    eFightingCharacterTextures(SDL_Renderer* const renderer) :
        eBasicCharacterTextures(renderer) {}

    std::vector<eTextureCollection> fFight;
};

struct eFireFighterTextures : public eBasicCharacterTextures {
    eFireFighterTextures(SDL_Renderer* const renderer) :
        eBasicCharacterTextures(renderer) {}

    std::vector<eTextureCollection> fCarry;
    std::vector<eTextureCollection> fPutOut;
};

struct eAnimalTextures : public eBasicCharacterTextures {
    eAnimalTextures(SDL_Renderer* const renderer) :
        eBasicCharacterTextures(renderer) {}

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

    eBasicCharacterTextures fFoodDistributor;
    eBasicCharacterTextures fActor;
    eBasicCharacterTextures fTaxCollector;
    eBasicCharacterTextures fWaterDistributor;
    eFightingCharacterTextures fWatchman;
    eFireFighterTextures fFireFighter;
    eBasicCharacterTextures fHealer;
    eBasicCharacterTextures fGymnast;
    eBasicCharacterTextures fPhilosopher;

    eResourceCollectorTextures fSilverMiner;
    eResourceCollectorTextures fBronzeMiner;
    eResourceCollectorTextures fLumberjack;

    eResourceCollectorTextures fHunter;

    eAnimalTextures fBoar;
};

#endif // ECHARACTERTEXTURES_H
