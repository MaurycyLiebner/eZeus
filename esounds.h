#ifndef ESOUNDS_H
#define ESOUNDS_H

#include <string>
#include <vector>

#include <SDL2/SDL_mixer.h>

class eTile;

class eSounds {
public:
    eSounds();
    ~eSounds();

    static void load();
    static bool loaded();

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
private:
    void loadImpl();

    static eSounds sInstance;

    bool mLoaded{false};

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
};

#endif // ESOUNDS_H
