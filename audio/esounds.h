#ifndef ESOUNDS_H
#define ESOUNDS_H

#include <string>
#include <vector>

#include <SDL2/SDL_mixer.h>

#include "egodsounds.h"
#include "eherosounds.h"
#include "emonstersounds.h"

class eTile;

class eSounds {
public:
    eSounds();
    ~eSounds();

    static void loadButtonSound();

    static void load();
    static bool loaded();

    static void playButtonSound();

    static void playSoundForTile(eTile* const tile);

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

    static void playFountainSound();
    static void playTaxesSound();
    static void playPalaceSound();
    static void playMaintananceSound();

    static void playFoundrySound();
    static void playMintSound();
    static void playTimberMillSound();

    static void playArmorySound();

    static void playHuntingSound();
    static void playBoarSound();
    static void playDeerSound();
    static void playWolfSound();

    static void playSheepSound();
    static void playGoatSound();
    static void playCattleSound();

    static void playStorageSound();

    static void playFoodVendorSound();
    static void playFleeceVendorSound();
    static void playOilVendorSound();
    static void playWineVendorSound();
    static void playArmsVendorSound();
    static void playHorseTrainerSound();

    static void playFireSound();
    static void playCollapseSound();

    static void playFireballHitSound();

    static void playCopperMinerSound();
    static void playSilverMinerSound();
    static void playStoneCutterSound();
    static void playTreeCutterSound();

    static void playArtisanSound();

    static void playGodSound(const eGodType g,
                             const eGodSound s);
    static void playHeroSound(const eHeroType h,
                              const eHeroSound s);

    static void playAttackSound(eCharacter* const c);
    static void playDieSound(eCharacter* const c);
    static void playHitSound(eCharacter* const c);

    static Mix_Chunk* loadSoundBase(const std::string& path);
private:
    void loadImpl();

    static eSounds sInstance;

    bool mLoaded{false};

    Mix_Chunk* mButton = nullptr;

    std::vector<Mix_Chunk*> mEnvironment;

    std::vector<Mix_Chunk*> mMaintenance;
    std::vector<Mix_Chunk*> mCommonHousing;
    std::vector<Mix_Chunk*> mEliteHousing;
    std::vector<Mix_Chunk*> mFarming;
    std::vector<Mix_Chunk*> mOrchard;
    std::vector<Mix_Chunk*> mSheepFarm;
    std::vector<Mix_Chunk*> mGoatFarm;
    std::vector<Mix_Chunk*> mSea;
    std::vector<Mix_Chunk*> mTriremeWharf;
    std::vector<Mix_Chunk*> mHunting;
    std::vector<Mix_Chunk*> mTimberMill;
    std::vector<Mix_Chunk*> mMarble;
    std::vector<Mix_Chunk*> mMint;
    std::vector<Mix_Chunk*> mFoundry;
    std::vector<Mix_Chunk*> mWorkshops;
    std::vector<Mix_Chunk*> mStorage;
    std::vector<Mix_Chunk*> mAgoraFood;
    std::vector<Mix_Chunk*> mAgoraFleece;
    std::vector<Mix_Chunk*> mAgoraOil;
    std::vector<Mix_Chunk*> mAgoraWine;
    std::vector<Mix_Chunk*> mAgoraArms;
    std::vector<Mix_Chunk*> mAgoraHorse;
    std::vector<Mix_Chunk*> mTrade;
    std::vector<Mix_Chunk*> mTaxes;
    std::vector<Mix_Chunk*> mPalace;
    std::vector<Mix_Chunk*> mDefensive;
    std::vector<Mix_Chunk*> mInfirmary;
    std::vector<Mix_Chunk*> mTheatre;
    std::vector<Mix_Chunk*> mDrama;
    std::vector<Mix_Chunk*> mPhilosophy;
    std::vector<Mix_Chunk*> mGymnasium;
    std::vector<Mix_Chunk*> mStadium;
    std::vector<Mix_Chunk*> mSanctuary;
    std::vector<Mix_Chunk*> mArmory;
    std::vector<Mix_Chunk*> mHorseRanch;
    std::vector<Mix_Chunk*> mBeautification;
    std::vector<Mix_Chunk*> mFountain;
    std::vector<Mix_Chunk*> mArtisansGuild;

    // terrain
    std::vector<Mix_Chunk*> mMeadow;
    std::vector<Mix_Chunk*> mFarmland;
    std::vector<Mix_Chunk*> mBeach;
    std::vector<Mix_Chunk*> mRocky;
    std::vector<Mix_Chunk*> mVegetation;
    std::vector<Mix_Chunk*> mWater;
    // animals
    std::vector<Mix_Chunk*> mBoar;
    std::vector<Mix_Chunk*> mGoat;
    std::vector<Mix_Chunk*> mWolf;
    std::vector<Mix_Chunk*> mSheep;
    std::vector<Mix_Chunk*> mCattle;
    std::vector<Mix_Chunk*> mDeer;

    // collectors
    std::vector<Mix_Chunk*> mCopperMiner;
    std::vector<Mix_Chunk*> mSilverMiner;
    std::vector<Mix_Chunk*> mTreeCutter;
    std::vector<Mix_Chunk*> mStoneCutter;

    std::vector<Mix_Chunk*> mArtisan;

    // rockthrower
    Mix_Chunk* mActorDie = nullptr;
    Mix_Chunk* mActorHit = nullptr;

    std::vector<Mix_Chunk*> mRockthrowerAttack;
    std::vector<Mix_Chunk*> mRockthrowerDie;
    Mix_Chunk* mRockthrowerHit = nullptr;

    Mix_Chunk* mBoarAttack = nullptr;
    Mix_Chunk* mBoarDie = nullptr;
    Mix_Chunk* mBoarHit = nullptr;

    Mix_Chunk* mBoarHunterAttack = nullptr;
    Mix_Chunk* mBoarHunterDie = nullptr;
    Mix_Chunk* mBoarHunterHit = nullptr;

    Mix_Chunk* mDeerAttack = nullptr;
    Mix_Chunk* mDeerDie = nullptr;
    Mix_Chunk* mDeerHit = nullptr;

    Mix_Chunk* mHopliteDie = nullptr;
    std::vector<Mix_Chunk*> mHopliteAttack;
    Mix_Chunk* mHopliteHit = nullptr;

    std::vector<Mix_Chunk*> mGenDie;
    std::vector<Mix_Chunk*> mGenHit;

    // events
    Mix_Chunk* mFire = nullptr;
    Mix_Chunk* mCollapse = nullptr;

    Mix_Chunk* mFireballHit = nullptr;

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
