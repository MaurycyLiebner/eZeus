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
    using eBasicCharacterTextures::eBasicCharacterTextures;

    std::vector<eTextureCollection> fCarry;
    std::vector<eTextureCollection> fCollect;
};

struct eArtisanTextures : public eBasicCharacterTextures {
    using eBasicCharacterTextures::eBasicCharacterTextures;

    std::vector<eTextureCollection> fBuild;
    std::vector<eTextureCollection> fBuildStanding;
};

struct eShepherdTextures : public eResourceCollectorTextures {
    eShepherdTextures(SDL_Renderer* const renderer) :
        eResourceCollectorTextures(renderer), fFight(renderer) {}

    eTextureCollection fFight;
};

struct eOrangeTenderTextures : public eBasicCharacterTextures {
    using eBasicCharacterTextures::eBasicCharacterTextures;

    std::vector<eTextureCollection> fWorkOnTree;
    std::vector<eTextureCollection> fCollect;
};

struct eGrowerTextures : public eBasicCharacterTextures {
    using eBasicCharacterTextures::eBasicCharacterTextures;

    std::vector<eTextureCollection> fWorkOnGrapes;
    std::vector<eTextureCollection> fWorkOnOlives;

    std::vector<eTextureCollection> fCollectGrapes;
    std::vector<eTextureCollection> fCollectOlives;
};

struct eFightingCharacterTextures : public eBasicCharacterTextures {
    using eBasicCharacterTextures::eBasicCharacterTextures;

    std::vector<eTextureCollection> fFight;
};

struct eFireFighterTextures : public eBasicCharacterTextures {
    using eBasicCharacterTextures::eBasicCharacterTextures;

    std::vector<eTextureCollection> fCarry;
    std::vector<eTextureCollection> fPutOut;
};

struct eAnimalTextures : public eBasicCharacterTextures {
    using eBasicCharacterTextures::eBasicCharacterTextures;

    std::vector<eTextureCollection> fFight;
    std::vector<eTextureCollection> fLayDown;
};

struct eArcherTextures : public eFightingCharacterTextures {
    using eFightingCharacterTextures::eFightingCharacterTextures;

    std::vector<eTextureCollection> fPatrol;
};

struct eRockThrowerTextures : public eFightingCharacterTextures {
    using eFightingCharacterTextures::eFightingCharacterTextures;

    std::vector<eTextureCollection> fFight2;
};

class eCharacterTextures {
public:
    eCharacterTextures(const int tileW, const int tileH,
                       SDL_Renderer* const renderer);

    void load();

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

//    eBasicCharacterTextures fFoodDistributor;
    eBasicCharacterTextures fActor;
    eBasicCharacterTextures fTaxCollector;
    eBasicCharacterTextures fWaterDistributor;
    eFightingCharacterTextures fWatchman;
    eFireFighterTextures fFireFighter;
    eBasicCharacterTextures fHealer;
    eBasicCharacterTextures fGymnast;
    eBasicCharacterTextures fPhilosopher;

    eBasicCharacterTextures fOx;
    eBasicCharacterTextures fOxHandler;

    eTextureCollection fEmptyTrailer;
    eTextureCollection fWoodTrailer1;
    eTextureCollection fWoodTrailer2;
    eTextureCollection fMarbleTrailer1;
    eTextureCollection fMarbleTrailer2;
    eTextureCollection fSculptureTrailer;

    eTextureCollection fEmptyBigTrailer;
    eTextureCollection fMarbleBigTrailer;

    eResourceCollectorTextures fMarbleMiner;
    eResourceCollectorTextures fSilverMiner;
    eResourceCollectorTextures fBronzeMiner;
    eResourceCollectorTextures fLumberjack;

    eArtisanTextures fArtisan;

    eResourceCollectorTextures fHunter;
    eResourceCollectorTextures fDeerHunter;

    eShepherdTextures fShepherd;
    eShepherdTextures fGoatherd;

    eBasicCharacterTextures fFoodVendor;
    eBasicCharacterTextures fFleeceVendor;
    eBasicCharacterTextures fOilVendor;
    eBasicCharacterTextures fWineVendor;
    eBasicCharacterTextures fArmsVendor;
    eBasicCharacterTextures fHorseVendor;

    eGrowerTextures fGrower;

    eAnimalTextures fBoar;
    eAnimalTextures fDeer;
    eAnimalTextures fWolf;

    eAnimalTextures fGoat;
    eAnimalTextures fNudeSheep;
    eAnimalTextures fFleecedSheep;

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

    std::vector<eTextureCollection> fOrangesCart;

    std::vector<eTextureCollection> fFoodCart;

    eOrangeTenderTextures fOrangeTender;

    eArcherTextures fArcher;

    eRockThrowerTextures fRockThrower;
    eFightingCharacterTextures fHoplite;
    eFightingCharacterTextures fHorseman;
};

#endif // ECHARACTERTEXTURES_H
