#ifndef ESOUNDS_H
#define ESOUNDS_H

#include <string>
#include <vector>

#include <SDL2/SDL_mixer.h>

class eTile;

struct eGodSounds {
    eGodSounds(const std::string& shortName,
               const std::string& longName) :
        fShortName(shortName),
        fLongName(longName) {

    }

    void load();

    void playVisit() {
        int id;
        if(fFirstVisit) {
            fFirstVisit = false;
            id = 2;
        } else {
            id = rand() % 3;
        }
        Mix_PlayChannel(-1, mVisit[id], 0);
    }

    void playAttack() {
        Mix_PlayChannel(-1, mAttack, 0);
    }

    void playAppear() {
        Mix_PlayChannel(-1, mAppear, 0);
    }

    void playDisappear() {
        Mix_PlayChannel(-1, mDisappear, 0);
    }

    const std::string fShortName;
    const std::string fLongName;

    bool fFirstVisit = true;
    std::vector<Mix_Chunk*> mVisit;
    Mix_Chunk* mAttack = nullptr;
    Mix_Chunk* mAppear = nullptr;
    Mix_Chunk* mDisappear = nullptr;
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

    static void playDemeterVisitSound();
    static void playDemeterAttackSound();

    static void playDemeterAppearSound();
    static void playDemeterDisappearSound();

    static void playAthenaVisitSound();
    static void playAthenaAttackSound();

    static void playAthenaAppearSound();
    static void playAthenaDisappearSound();
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
    std::vector<Mix_Chunk*> mArtisan;

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

    // events
    Mix_Chunk* mFire = nullptr;
    Mix_Chunk* mCollapse = nullptr;

    eGodSounds mAthena{"Atn", "athena"};
    eGodSounds mDemeter{"Dem", "demeter"};
};

#endif // ESOUNDS_H
