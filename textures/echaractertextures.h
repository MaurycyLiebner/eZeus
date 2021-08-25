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

struct eGrowerTextures : public eBasicCharacterTextures {
    eGrowerTextures(SDL_Renderer* const renderer) :
        eBasicCharacterTextures(renderer) {}

    std::vector<eTextureCollection> fWorkOnGrapes;
    std::vector<eTextureCollection> fWorkOnOlives;

    std::vector<eTextureCollection> fCollectGrapes;
    std::vector<eTextureCollection> fCollectOlives;
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
    std::vector<eTextureCollection> fLayDown;
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
    eResourceCollectorTextures fDeerHunter;

    eResourceCollectorTextures fShepherd;
    eResourceCollectorTextures fGoatherd;

    eGrowerTextures fGrower;

    eAnimalTextures fBoar;
    eAnimalTextures fDeer;
    eAnimalTextures fWolf;

    eAnimalTextures fGoat;
    eAnimalTextures fNudeSheep;
    eAnimalTextures fSheep;

    eBasicCharacterTextures fSettlers1;
    eBasicCharacterTextures fSettlers2;

    eBasicCharacterTextures fTransporter;

    eTextureCollection fEmptyCart;
    std::vector<eTextureCollection> fUrchinCart;
    std::vector<eTextureCollection> fFishCart;
    std::vector<eTextureCollection> fMeatCart;
    std::vector<eTextureCollection> fCheeseCart;
    std::vector<eTextureCollection> fCarrotsCart;
    std::vector<eTextureCollection> fOnionsCart;
    std::vector<eTextureCollection> fWheatCart;
    std::vector<eTextureCollection> fBronzeCart;
    std::vector<eTextureCollection> fGrapesCart;
    std::vector<eTextureCollection> fOlivesCart;
    std::vector<eTextureCollection> fFleeceCart;
    std::vector<eTextureCollection> fArmorCart;
    std::vector<eTextureCollection> fOliveOilCart;
    std::vector<eTextureCollection> fWineCart;

};

#endif // ECHARACTERTEXTURES_H
