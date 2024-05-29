#ifndef ESOUNDS_H
#define ESOUNDS_H

#include <string>
#include <vector>

#include <SDL2/SDL_mixer.h>

#include "egodsounds.h"
#include "eherosounds.h"
#include "emonstersounds.h"

class eTile;

class eSoundVector {
public:
    int soundCount() const { return mPaths.size(); }

    void addPath(const std::string& path) {
        mPaths.push_back({nullptr, path});
    }

    void deleteSounds() const {
        for(const auto& s : mPaths) {
            if(!s.first) continue;
            Mix_FreeChunk(s.first);
        }
    }

    void play(const int id);
private:
    std::vector<std::pair<Mix_Chunk*, std::string>> mPaths;
};

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

    static void playArtisansGuildSound();

    static void playFountainSound();
    static void playTaxesSound();
    static void playPalaceSound();
    static void playMaintananceSound();

    static void playFoundrySound();
    static void playMintSound();
    static void playTimberMillSound();

    static void playArmorySound();
    static void playHorseRanchSound();

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

    eSoundVector mEnvironment;

    eSoundVector mMaintenance;
    eSoundVector mCommonHousing;
    eSoundVector mEliteHousing;
    eSoundVector mFarming;
    eSoundVector mOrchard;
    eSoundVector mSheepFarm;
    eSoundVector mGoatFarm;
    eSoundVector mSea;
    eSoundVector mTriremeWharf;
    eSoundVector mHunting;
    eSoundVector mTimberMill;
    eSoundVector mMarble;
    eSoundVector mMint;
    eSoundVector mFoundry;
    eSoundVector mWorkshops;
    eSoundVector mStorage;
    eSoundVector mAgoraFood;
    eSoundVector mAgoraFleece;
    eSoundVector mAgoraOil;
    eSoundVector mAgoraWine;
    eSoundVector mAgoraArms;
    eSoundVector mAgoraHorse;
    eSoundVector mTrade;
    eSoundVector mTaxes;
    eSoundVector mPalace;
    eSoundVector mDefensive;
    eSoundVector mInfirmary;
    eSoundVector mTheatre;
    eSoundVector mDrama;
    eSoundVector mPhilosophy;
    eSoundVector mGymnasium;
    eSoundVector mStadium;
    eSoundVector mSanctuary;
    eSoundVector mArmory;
    eSoundVector mHorseRanch;
    eSoundVector mBeautification;
    eSoundVector mFountain;
    eSoundVector mArtisansGuild;

    // terrain
    eSoundVector mMeadow;
    eSoundVector mFarmland;
    eSoundVector mBeach;
    eSoundVector mRocky;
    eSoundVector mVegetation;
    eSoundVector mWater;
    // animals
    eSoundVector mBoar;
    eSoundVector mGoat;
    eSoundVector mWolf;
    eSoundVector mSheep;
    eSoundVector mCattle;
    eSoundVector mDeer;

    // collectors
    eSoundVector mCopperMiner;
    eSoundVector mSilverMiner;
    eSoundVector mTreeCutter;
    eSoundVector mStoneCutter;

    eSoundVector mArtisan;

    // rockthrower
    Mix_Chunk* mActorDie = nullptr;
    Mix_Chunk* mActorHit = nullptr;

    eSoundVector mRockthrowerAttack;
    eSoundVector mRockthrowerDie;
    Mix_Chunk* mRockthrowerHit = nullptr;

    eSoundVector mArcherAttack;
    Mix_Chunk* mArcherHit = nullptr;
    Mix_Chunk* mArcherDie = nullptr;

    Mix_Chunk* mOutlawHit = nullptr;
    Mix_Chunk* mOutlawDie = nullptr;
    Mix_Chunk* mOutlawAttack = nullptr;

    eSoundVector mAresWarriorAttack;
    Mix_Chunk* mAresWarriorHit = nullptr;
    Mix_Chunk* mAresWarriorDie = nullptr;

    Mix_Chunk* mTrojanHorseDie = nullptr;
    Mix_Chunk* mTrojanHorseHit = nullptr;

    Mix_Chunk* mTrojanSpearthrowerDie = nullptr;
    Mix_Chunk* mTrojanSpearthrowerHit = nullptr;
    eSoundVector mTrojanSpearthrowerAttack;

    Mix_Chunk* mTrojanSwordDie = nullptr;
    Mix_Chunk* mTrojanSwordHit = nullptr;
    eSoundVector mTrojanSwordAttack;

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
    eSoundVector mHopliteAttack;
    Mix_Chunk* mHopliteHit = nullptr;

    eSoundVector mGenDie;
    eSoundVector mGenHit;

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
