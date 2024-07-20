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

struct eUrchinGathererTextures {
    eUrchinGathererTextures(SDL_Renderer* const renderer) :
        fDie(renderer) {}

    std::vector<eTextureCollection> fSwim;
    std::vector<eTextureCollection> fCollect;
    std::vector<eTextureCollection> fCarry;
    std::vector<eTextureCollection> fDeposit;
    eTextureCollection fDie;
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

struct eShepherdTextures : public eBasicCharacterTextures {
    eShepherdTextures(SDL_Renderer* const renderer) :
        eBasicCharacterTextures(renderer),
        fCollect(renderer),
        fFight(renderer) {}

    std::vector<eTextureCollection> fCarry;
    eTextureCollection fCollect;
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

struct eCattleTextures : public eBasicCharacterTextures {
    using eBasicCharacterTextures::eBasicCharacterTextures;

    std::vector<eTextureCollection> fStand;
};

struct eBullTextures : public eCattleTextures {
    using eCattleTextures::eCattleTextures;

    std::vector<eTextureCollection> fAttack;
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

struct eAresWarriorTextures {
    std::vector<eTextureCollection> fWalk;
    std::vector<eTextureCollection> fDie;
    std::vector<eTextureCollection> fFight;
};

struct eChariotTextures {
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
    bool fOrichalcMinerLoaded = false;
    void loadOrichalcMiner();
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
    bool fPoseidonTowerArcherLoaded = false;
    void loadPoseidonTowerArcher();
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

    bool fAmazonSpearLoaded = false;
    void loadAmazonSpear();
    bool fAmazonArcherLoaded = false;
    void loadAmazonArcher();

    bool fTrojanHopliteLoaded = false;
    void loadTrojanHoplite();
    bool fTrojanSpearthrowerLoaded = false;
    void loadTrojanSpearthrower();
    bool fTrojanHorsemanLoaded = false;
    void loadTrojanHorseman();

    bool fCentaurHorsemanLoaded = false;
    void loadCentaurHorseman();
    bool fCentaurArcherLoaded = false;
    void loadCentaurArcher();

    bool fPersianHopliteLoaded = false;
    void loadPersianHoplite();
    bool fPersianHorsemanLoaded = false;
    void loadPersianHorseman();
    bool fPersianArcherLoaded = false;
    void loadPersianArcher();

    bool fEgyptianHopliteLoaded = false;
    void loadEgyptianHoplite();
    bool fEgyptianChariotLoaded = false;
    void loadEgyptianChariot();
    bool fEgyptianArcherLoaded = false;
    void loadEgyptianArcher();

    bool fMayanHopliteLoaded = false;
    void loadMayanHoplite();
    bool fMayanArcherLoaded = false;
    void loadMayanArcher();

    bool fOceanidHopliteLoaded = false;
    void loadOceanidHoplite();
    bool fOceanidSpearthrowerLoaded = false;
    void loadOceanidSpearthrower();

    bool fPhoenicianHorsemanLoaded = false;
    void loadPhoenicianHorseman();
    bool fPhoenicianArcherLoaded = false;
    void loadPhoenicianArcher();

    bool fAtlanteanHopliteLoaded = false;
    void loadAtlanteanHoplite();
    bool fAtlanteanChariotLoaded = false;
    void loadAtlanteanChariot();
    bool fAtlanteanArcherLoaded = false;
    void loadAtlanteanArcher();

    bool fAresWarriorLoaded = false;
    void loadAresWarrior();

    bool fHealerLoaded = false;
    void loadHealer();
    bool fCartLoaded = false;
    void loadCart();
    void loadOrangesCart();
    bool fBoarLoaded = false;
    void loadBoar();
    bool fGymnastLoaded = false;
    void loadGymnast();
    bool fCompetitorLoaded = false;
    void loadCompetitor();
    bool fGoatLoaded = false;
    void loadGoat();
    bool fWolfLoaded = false;
    void loadWolf();
    bool fHunterLoaded = false;
    void loadHunter();
    void loadDeerHunter();
    bool fPhilosopherLoaded = false;
    void loadPhilosopher();
    bool fUrchinGathererLoaded = false;
    void loadUrchinGatherer();
    bool fFishingBoatLoaded = false;
    void loadFishingBoat();
    bool fTradeBoatLoaded = false;
    void loadTradeBoat();
    bool fTriremeLoaded = false;
    void loadTrireme();
    bool fTriremeOverlayLoaded = false;
    void loadTriremeOverlay();
    bool fEnemyBoatLoaded = false;
    void loadEnemyBoat();
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

    bool fDisgruntledLoaded = false;
    void loadDisgruntled();
    bool fSickLoaded = false;
    void loadSick();
    bool fHomelessLoaded = false;
    void loadHomeless();

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

    bool fScholarLoaded = false;
    void loadScholar();
    bool fAstronomerLoaded = false;
    void loadAstronomer();
    bool fInventorLoaded = false;
    void loadInventor();
    bool fCuratorLoaded = false;
    void loadCurator();

    bool fHoplitePoseidonLoaded = false;
    void loadHoplitePoseidon();
    bool fArcherPoseidonLoaded = false;
    void loadArcherPoseidon();
    bool fChariotPoseidonLoaded = false;
    void loadChariotPoseidon();

    bool fCattleLoaded = false;
    void loadCattle();
    bool fBullLoaded = false;
    void loadBull();
    bool fButcherLoaded = false;
    void loadButcher();

    bool fChariotVendorLoaded = false;
    void loadChariotVendor();

    bool fChariotLoaded = false;
    void loadChariot();

    bool fElephantLoaded = false;
    void loadElephant();

    bool fSatyrLoaded = false;
    void loadSatyr();

    void loadBanners();
    bool fBannersLoaded = false;

    void loadEliteCitizen();
    bool fEliteCitizenLoaded = false;

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
    eBasicCharacterTextures fCompetitor;
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
    eResourceCollectorTextures fOrichalcMiner;
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

    eCattleTextures fCattle1;
    eCattleTextures fCattle2;
    eCattleTextures fCattle3;
    eBullTextures fBull;
    eBasicCharacterTextures fButcher;

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

    eOrangeTenderTextures fOrangeTender;

    eArcherTextures fArcher;
    eArcherTextures fPoseidonTowerArcher;

    eRockThrowerTextures fRockThrower;
    eFightingCharacterTextures fHoplite;
    eFightingCharacterTextures fHorseman;

    eFightingCharacterTextures fHoplitePoseidon;
    eChariotTextures fChariotPoseidon;
    eFightingCharacterTextures fArcherPoseidon;

    eRockThrowerTextures fGreekRockThrower;
    eFightingCharacterTextures fGreekHoplite;
    eFightingCharacterTextures fGreekHorseman;

    eFightingCharacterTextures fAmazonSpear;
    eFightingCharacterTextures fAmazonArcher;

    eFightingCharacterTextures fTrojanHoplite;
    eFightingCharacterTextures fTrojanSpearthrower;
    eFightingCharacterTextures fTrojanHorseman;

    eFightingCharacterTextures fCentaurHorseman;
    eFightingCharacterTextures fCentaurArcher;

    eFightingCharacterTextures fEgyptianHoplite;
    eChariotTextures fEgyptianChariot;
    eFightingCharacterTextures fEgyptianArcher;

    eFightingCharacterTextures fMayanHoplite;
    eFightingCharacterTextures fMayanArcher;

    eFightingCharacterTextures fPhoenicianHorseman;
    eFightingCharacterTextures fPhoenicianArcher;

    eFightingCharacterTextures fOceanidHoplite;
    eFightingCharacterTextures fOceanidSpearthrower;

    eFightingCharacterTextures fPersianHoplite;
    eFightingCharacterTextures fPersianHorseman;
    eFightingCharacterTextures fPersianArcher;

    eFightingCharacterTextures fAtlanteanHoplite;
    eChariotTextures fAtlanteanChariot;
    eFightingCharacterTextures fAtlanteanArcher;

    eAresWarriorTextures fAresWarrior;

    eTextureCollection fBannerRod;
    std::vector<eTextureCollection> fBanners;
    eTextureCollection fBannerTops;
    eTextureCollection fPoseidonBannerTops;

    eBasicCharacterTextures fTrader;
    eBasicCharacterTextures fDonkey;

    eBasicCharacterTextures fPorter;

    eFishingBoatTextures fFishingBoat;
    eUrchinGathererTextures fUrchinGatherer;
    eTradeBoatTextures fTradeBoat;
    eTradeBoatTextures fTrireme;
    std::vector<eTextureCollection> fTriremeOverlay;
    std::vector<eTextureCollection> fTriremeDieOverlay;
    eTradeBoatTextures fEnemyBoat;

    eFightingCharacterTextures fDisgruntled;
    eFightingCharacterTextures fSick;
    eBasicCharacterTextures fHomeless;

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

    eMonsterTextures fSatyr;

    eHeroTextures fAchilles;
    eHeroTextures fAtalanta;
    eHeroTextures fBellerophon;
    eHeroTextures fHercules;
    eHeroTextures fJason;
    eHeroTextures fOdysseus;
    eHeroTextures fPerseus;
    eHeroTextures fTheseus;

    eBasicCharacterTextures fScholar;
    eBasicCharacterTextures fAstronomer;
    eBasicCharacterTextures fInventor;
    eBasicCharacterTextures fCurator;

    eBasicCharacterTextures fChariotVendor;
    std::vector<eTextureCollection> fChariot;

    eBasicCharacterTextures fElephant;

    eFightingCharacterTextures fEliteCitizen;
};

#endif // ECHARACTERTEXTURES_H
