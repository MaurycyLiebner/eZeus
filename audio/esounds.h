#ifndef ESOUNDS_H
#define ESOUNDS_H

#include "esoundvector.h"

#include "egodsounds.h"
#include "eherosounds.h"
#include "emonstersounds.h"

class eTile;

class eSounds {
public:
    eSounds();

    static void loadButtonSound();

    static void load();
    static bool loaded();

    static void playButtonSound();

    static void playSoundForTile(eTile* const tile);
    static bool playSoundForBuilding(eBuilding* const b);
    static bool playSoundForCharacter(eCharacter* const c);
    static bool playSoundForTerrain(const eTerrain terrain);

    static void playEnvironmentSound();

    static void playBeachSound();
    static void playWaterSound();
    static void playRockySound();

    static void playCommonHousingSound();

    static void playTheatreSound();
    static void playDramaSound();
    static void playPhilosophySound();
    static void playGymnasiumSound();
    static void playStadiumSound();

    static void playUniversitySound();
    static void playObservatorySound();
    static void playInventorsWorkshopSound();
    static void playLaboratorySound();
    static void playMuseumSound();

    static void playArtisansGuildSound();

    static void playFountainSound();
    static void playInfirmarySound();
    static void playTaxesSound();
    static void playPalaceSound();
    static void playMaintananceSound();

    static void playFoundrySound();
    static void playMintSound();
    static void playTimberMillSound();

    static void playArmorySound();
    static void playHorseRanchSound();
    static void playChariotFactorySound();

    static void playHuntingSound();
    static void playBoarSound();
    static void playDeerSound();
    static void playWolfSound();

    static void playSheepSound();
    static void playGoatSound();
    static void playCattleSound();
    static void playCorralSound();
    static void playFruitLodgeSound();

    static void playStorageSound();

    static void playFoodVendorSound();
    static void playFleeceVendorSound();
    static void playOilVendorSound();
    static void playWineVendorSound();
    static void playArmsVendorSound();
    static void playHorseTrainerSound();
    static void playChariotVendorSound();

    static void playTradeSound();

    static void playFireSound();
    static void playCollapseSound();

    static void playFireballHitSound();

    static void playCopperMinerSound();
    static void playSilverMinerSound();
    static void playStoneCutterSound();
    static void playTreeCutterSound();

    static void playArtisanSound();

    static void playUrchinSound();

    static void playGodSound(const eGodType g,
                             const eGodSound s);
    static void playHeroSound(const eHeroType h,
                              const eHeroSound s);

    static void playAttackSound(eCharacter* const c);
    static void playDieSound(eCharacter* const c);
    static void playHitSound(eCharacter* const c);
private:
    void loadImpl();

    static eSounds sInstance;

    bool mLoaded{false};

    std::shared_ptr<eSoundVector> mButton = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mEnvironment = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mMaintenance = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mCommonHousing = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mEliteHousing = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mFarming = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mCorral = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mFruitLodge = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mOrchard = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mSheepFarm = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mGoatFarm = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mSea = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mTriremeWharf = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mHunting = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mTimberMill = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mMarble = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mMint = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mFoundry = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mWorkshops = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mStorage = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mAgoraFood = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mAgoraFleece = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mAgoraOil = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mAgoraWine = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mAgoraArms = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mAgoraHorse = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mAgoraChariot = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mTrade = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mTaxes = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mPalace = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mDefensive = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mInfirmary = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mTheatre = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mDrama = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mPhilosophy = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mGymnasium = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mStadium = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mSanctuary = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mArmory = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mHorseRanch = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mBeautification = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mFountain = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mArtisansGuild = std::make_shared<eSoundVector>();

    // terrain
    std::shared_ptr<eSoundVector> mMeadow = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mFarmland = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mBeach = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mRocky = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mVegetation = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mWater = std::make_shared<eSoundVector>();
    // animals
    std::shared_ptr<eSoundVector> mBoar = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mGoat = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mWolf = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mSheep = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mCattle = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mDeer = std::make_shared<eSoundVector>();

    // collectors
    std::shared_ptr<eSoundVector> mCopperMiner = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mSilverMiner = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mTreeCutter = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mStoneCutter = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mArtisan = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mUrchin = std::make_shared<eSoundVector>();

    // science
    std::shared_ptr<eSoundVector> mUniversity = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mObservatory = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mInventorsWorkshop = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mLaboratory = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mMuseum = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mChariotFactory = std::make_shared<eSoundVector>();

    // rockthrower
    std::shared_ptr<eSoundVector> mActorDie = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mActorHit = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mRockthrowerAttack = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mRockthrowerDie = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mRockthrowerHit = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mArcherAttack = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mArcherHit = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mArcherDie = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mOutlawHit = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mOutlawDie = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mOutlawAttack = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mAresWarriorAttack = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mAresWarriorHit = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mAresWarriorDie = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mTrojanHorseDie = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mTrojanHorseHit = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mTrojanSpearthrowerDie = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mTrojanSpearthrowerHit = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mTrojanSpearthrowerAttack = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mTrojanSwordDie = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mTrojanSwordHit = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mTrojanSwordAttack = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mBoarAttack = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mBoarDie = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mBoarHit = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mBoarHunterAttack = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mBoarHunterDie = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mBoarHunterHit = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mDeerAttack = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mDeerDie = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mDeerHit = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mHopliteDie = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mHopliteAttack = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mHopliteHit = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mGenDie = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mGenHit = std::make_shared<eSoundVector>();

    // events
    std::shared_ptr<eSoundVector> mFire = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> mCollapse = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> mFireballHit = std::make_shared<eSoundVector>();

    eGodSounds mAphrodite{"Aph", "aphrodite"};
    eGodSounds mApollo{"Apo", "apollo"};
    eGodSounds mAres{"Are", "ares"};
    eGodSounds mArtemis{"Atm", "artemis"};
    eGodSounds mAthena{"Atn", "athena"};
    eGodSounds mAtlas{"Ats", "Atlas"};
    eGodSounds mDemeter{"Dem", "demeter"};
    eGodSounds mDionysus{"Dio", "dionysus"};
    eGodSounds mHades{"Had", "hades"};
    eGodSounds mHephaestus{"Hep", "hephaestus"};
    eGodSounds mHera{"Hra", "Hera"};
    eGodSounds mHermes{"Her", "hermes"};
    eGodSounds mPoseidon{"Pos", "poseidon"};
    eGodSounds mZeus{"Zeu", "zeus"};

    eHeroSounds mAchilles{"Ach", "achilles"};
    eHeroSounds mAtalanta{"Ata", "atalanta"};
    eHeroSounds mBellerophon{"Bel", "bellerophon"};
    eHeroSounds mHercules{"Hec", "hercules"};
    eHeroSounds mJason{"Jas", "jason"};
    eHeroSounds mOdysseus{"Ody", "odysseus"};
    eHeroSounds mPerseus{"Per", "perseus"};
    eHeroSounds mTheseus{"The", "theseus"};

    eMonsterSounds mCalydonianBoar{"cal", "calydonian"};
    eMonsterSounds mCerberus{"cer", "cerberus"};
    eMonsterSounds mChimera{"chi", "chimera"};
    eMonsterSounds mCyclops{"cyc", "cyclops"};
    eMonsterSounds mDragon{"dra", "dragon"};
    eMonsterSounds mEchidna{"ech", "echidna"};
    eMonsterSounds mHarpies{"har", "harpies"};
    eMonsterSounds mHector{"hec", "hector"};
    eMonsterSounds mHydra{"hyd", "hydra"};
    eMonsterSounds mKraken{"kra", "kraken"};
    eMonsterSounds mMaenads{"mae", "maenads"};
    eMonsterSounds mMedusa{"med", "medusa"};
    eMonsterSounds mMinotaur{"min", "minotaur"};
    eMonsterSounds mScylla{"scy", "scylla"};
    eMonsterSounds mSphinx{"sph", "sphinx"};
    eMonsterSounds mTalos{"tal", "talos"};
};

#endif // ESOUNDS_H
