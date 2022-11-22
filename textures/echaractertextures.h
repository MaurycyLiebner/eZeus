#ifndef ECHARACTERTEXTURES_H
#define ECHARACTERTEXTURES_H

#include "etexturecollection.h"

struct eBasicCharacterTextures {
    eBasicCharacterTextures(SDL_Renderer* const renderer) :
        fDie(renderer) {}

    std::vector<eTextureCollection> fWalk;
    eTextureCollection fDie;
};

struct eFishingBoatTextures {
    eFishingBoatTextures(SDL_Renderer* const renderer) :
        fStand(renderer) {}

    eTextureCollection fStand;
    std::vector<eTextureCollection> fSwim;
    std::vector<eTextureCollection> fCollect;
    std::vector<eTextureCollection> fDie;
};

struct eTradeBoatTextures {
    eTradeBoatTextures(SDL_Renderer* const renderer) :
        fStand(renderer) {}

    eTextureCollection fStand;
    std::vector<eTextureCollection> fSwim;
    std::vector<eTextureCollection> fDie;
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

struct eHorseTextures : public eBasicCharacterTextures {
    using eBasicCharacterTextures::eBasicCharacterTextures;

    std::vector<eTextureCollection> fStand;
};

struct eArcherTextures : public eFightingCharacterTextures {
    using eFightingCharacterTextures::eFightingCharacterTextures;

    std::vector<eTextureCollection> fPatrol;
};

struct eRockThrowerTextures : public eFightingCharacterTextures {
    using eFightingCharacterTextures::eFightingCharacterTextures;

    std::vector<eTextureCollection> fFight2;
};

struct eMonsterTextures {
    std::vector<eTextureCollection> fWalk;
    std::vector<eTextureCollection> fDie;
    std::vector<eTextureCollection> fFight;
    std::vector<eTextureCollection> fFight2;
};

struct eHeroTextures {
    std::vector<eTextureCollection> fWalk;
    std::vector<eTextureCollection> fDie;
    std::vector<eTextureCollection> fFight;
};

struct eWaterMonsterTextures {
    eWaterMonsterTextures(SDL_Renderer* const renderer) :
        fDie(renderer) {}

    std::vector<eTextureCollection> fWalk;
    eTextureCollection fDie;
    std::vector<eTextureCollection> fFight;
    std::vector<eTextureCollection> fFight2;
};

class eCharacterTextures {
public:
    eCharacterTextures(const int tileW, const int tileH,
                       SDL_Renderer* const renderer);

    void loadPeddler();

    void load();

    bool fLoaded = false;

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

    eBasicCharacterTextures fPeddler;

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
    eHorseTextures fHorse;

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

    eRockThrowerTextures fGreekRockThrower;
    eFightingCharacterTextures fGreekHoplite;
    eFightingCharacterTextures fGreekHorseman;

    eTextureCollection fBannerRod;
    std::vector<eTextureCollection> fBanners;
    eTextureCollection fBannerTops;

    eBasicCharacterTextures fTrader;
    eBasicCharacterTextures fDonkey;

    eBasicCharacterTextures fPorter;

    eFishingBoatTextures fFishingBoat;
    eTradeBoatTextures fTradeBoat;

    eMonsterTextures fCalydonianBoar;
    eMonsterTextures fCerberus;
    eMonsterTextures fChimera;
    eMonsterTextures fCyclops;
    eMonsterTextures fDragon;
    eMonsterTextures fEchidna;
    eMonsterTextures fHarpies;
    eMonsterTextures fHector;
    eMonsterTextures fHydra;
    eWaterMonsterTextures fKraken;
    eMonsterTextures fMaenads;
    eMonsterTextures fMedusa;
    eMonsterTextures fMinotaur;
    eWaterMonsterTextures fScylla;
    eMonsterTextures fSphinx;
    eMonsterTextures fTalos;

    eHeroTextures fAchilles;
    eHeroTextures fAtalanta;
    eHeroTextures fBellerophon;
    eHeroTextures fHercules;
    eHeroTextures fJason;
    eHeroTextures fOdysseus;
    eHeroTextures fPerseus;
    eHeroTextures fTheseus;
};

#endif // ECHARACTERTEXTURES_H
