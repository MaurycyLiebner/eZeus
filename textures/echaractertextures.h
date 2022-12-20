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

    bool fPeddlerLoaded = false;
    void loadPeddler();
    bool fActorLoaded = false;
    void loadActor();
    bool fOxLoaded = false;
    void loadOx();
    bool fPorterLoaded = false;
    void loadPorter();
    bool fOxHandlerLoaded = false;
    void loadOxHandler();
    bool fTrailerLoaded = false;
    void loadTrailer();
    bool fSettlersLoaded = false;
    void loadSettlers();
    bool fFireFighterLoaded = false;
    void loadFireFighter();
    bool fWatchmanLoaded = false;
    void loadWatchman();
    bool fGoatherdLoaded = false;
    void loadGoatherd();
    bool fBronzeMinerLoaded = false;
    void loadBronzeMiner();
    bool fArtisanLoaded = false;
    void loadArtisan();
    bool fFoodVendorLoaded = false;
    void loadFoodVendor();
    bool fFleeceVendorLoaded = false;
    void loadFleeceVendor();
    bool fOilVendorLoaded = false;
    void loadOilVendor();
    bool fWineVendorLoaded = false;
    void loadWineVendor();
    bool fArmsVendorLoaded = false;
    void loadArmsVendor();
    bool fHorseVendorLoaded = false;
    void loadHorseVendor();
    bool fSheepLoaded = false;
    void loadSheep();
    bool fHorseLoaded = false;
    void loadHorse();
    bool fShepherdLoaded = false;
    void loadShepherd();
    bool fMarbleMinerLoaded = false;
    void loadMarbleMiner();
    bool fSilverMinerLoaded = false;
    void loadSilverMiner();
    bool fArcherLoaded = false;
    void loadArcher();
    bool fLumberjackLoaded = false;
    void loadLumberjack();
    bool fTaxCollectorLoaded = false;
    void loadTaxCollector();
    bool fTransporterLoaded = false;
    void loadTransporter();
    bool fGrowerLoaded = false;
    void loadGrower();
    void loadOrangeTender();
    bool fTraderLoaded = false;
    void loadTrader();
    bool fWaterDistributorLoaded = false;
    void loadWaterDistributor();
    bool fRockThrowerLoaded = false;
    void loadRockThrower();
    bool fHopliteLoaded = false;
    void loadHoplite();
    bool fHorsemanLoaded = false;
    void loadHorseman();
    bool fHealerLoaded = false;
    void loadHealer();
    bool fCartLoaded = false;
    void loadCart();
    void loadOrangesCart();
    bool fBoarLoaded = false;
    void loadBoar();
    bool fGymnastLoaded = false;
    void loadGymnast();
    bool fGoatLoaded = false;
    void loadGoat();
    bool fWolfLoaded = false;
    void loadWolf();
    bool fHunterLoaded = false;
    void loadHunter();
    void loadDeerHunter();
    bool fPhilosopherLoaded = false;
    void loadPhilosopher();
    bool fFishingBoatLoaded = false;
    void loadFishingBoat();
    bool fTradeBoatLoaded = false;
    void loadTradeBoat();
    bool fDeerLoaded = false;
    void loadDeer();
    bool fGreekHopliteLoaded = false;
    void loadGreekHoplite();
    bool fGreekHorsemanLoaded = false;
    void loadGreekHorseman();
    bool fGreekRockThrowerLoaded = false;
    void loadGreekRockThrower();
    bool fDonkeyLoaded = false;
    void loadDonkey();

    bool fCalydonianBoarLoaded = false;
    void loadCalydonianBoar();
    bool fCerberusLoaded = false;
    void loadCerberus();
    bool fChimeraLoaded = false;
    void loadChimera();
    bool fCyclopsLoaded = false;
    void loadCyclops();
    bool fDragonLoaded = false;
    void loadDragon();
    bool fEchidnaLoaded = false;
    void loadEchidna();
    bool fHarpieLoaded = false;
    void loadHarpie();
    bool fHectorLoaded = false;
    void loadHector();
    bool fHydraLoaded = false;
    void loadHydra();
    bool fKrakenLoaded = false;
    void loadKraken();
    bool fMaenadsLoaded = false;
    void loadMaenads();
    bool fMedusaLoaded = false;
    void loadMedusa();
    bool fMinotaurLoaded = false;
    void loadMinotaur();
    bool fScyllaLoaded = false;
    void loadScylla();
    bool fSphinxLoaded = false;
    void loadSphinx();
    bool fTalosLoaded = false;
    void loadTalos();

    bool fAchillesLoaded = false;
    void loadAchilles();
    bool fAtalantaLoaded = false;
    void loadAtalanta();
    bool fBellerophonLoaded = false;
    void loadBellerophon();
    bool fHeraclesLoaded = false;
    void loadHeracles();
    bool fJasonLoaded = false;
    void loadJason();
    bool fOdysseusLoaded = false;
    void loadOdysseus();
    bool fPerseusLoaded = false;
    void loadPerseus();
    bool fTheseusLoaded = false;
    void loadTheseus();

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
