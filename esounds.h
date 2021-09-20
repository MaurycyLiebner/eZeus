#ifndef ESOUNDS_H
#define ESOUNDS_H

#include <string>
#include <vector>

#include <SDL2/SDL_mixer.h>

#include "characters/gods/egod.h"

class eTile;

enum class eGodSound {
    visit,
    invade,
    appear,
    disappear,
    attack,
    curse,
    hit,
    santcify
};

struct eGodSounds {
    eGodSounds(const std::string& shortName,
               const std::string& longName) :
        fShortName(shortName),
        fLongName(longName) {

    }

    ~eGodSounds() {
        for(const auto v : fVisit) {
            Mix_FreeChunk(v);
        }
        Mix_FreeChunk(fInvade);
        Mix_FreeChunk(fAppear);
        Mix_FreeChunk(fDisappear);

        for(const auto a : fAttack) {
            Mix_FreeChunk(a);
        }
        Mix_FreeChunk(fCurse);
        Mix_FreeChunk(fHit);
        Mix_FreeChunk(fSanctify);
    }

    void load();

    void play(const eGodSound s) {
        switch(s) {
        case eGodSound::visit:
            playVisit();
            break;
        case eGodSound::invade:
            playInvade();
            break;
        case eGodSound::appear:
            playAppear();
            break;
        case eGodSound::disappear:
            playDisappear();
            break;
        case eGodSound::attack:
            playAttack();
            break;
        case eGodSound::curse:
            playCurse();
            break;
        case eGodSound::hit:
            playHit();
            break;
        case eGodSound::santcify:
            playSanctify();
            break;
        }
    }

    void playVisit() {
        int id;
        if(fFirstVisit) {
            fFirstVisit = false;
            id = 2;
        } else {
            id = rand() % 3;
        }
        Mix_PlayChannel(-1, fVisit[id], 0);
    }

    void playInvade() {
        Mix_PlayChannel(-1, fInvade, 0);
    }

    void playAppear() {
        Mix_PlayChannel(-1, fAppear, 0);
    }

    void playDisappear() {
        Mix_PlayChannel(-1, fDisappear, 0);
    }

    void playAttack() {
        const int id = rand() % fAttack.size();
        Mix_PlayChannel(-1, fAttack[id], 0);
    }

    void playCurse() {
        Mix_PlayChannel(-1, fCurse, 0);
    }

    void playHit() {
        Mix_PlayChannel(-1, fHit, 0);
    }

    void playSanctify() {
        Mix_PlayChannel(-1, fSanctify, 0);
    }

    const std::string fShortName;
    const std::string fLongName;

    bool fFirstVisit = true;

    std::vector<Mix_Chunk*> fVisit;
    Mix_Chunk* fInvade = nullptr;
    Mix_Chunk* fAppear = nullptr;
    Mix_Chunk* fDisappear = nullptr;

    std::vector<Mix_Chunk*> fAttack;
    Mix_Chunk* fCurse = nullptr;
    Mix_Chunk* fHit = nullptr;
    Mix_Chunk* fSanctify = nullptr;
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

    static void playCopperMinerSound();
    static void playSilverMinerSound();
    static void playStoneCutterSound();
    static void playTreeCutterSound();

    static void playGodSound(const eGodType g,
                             const eGodSound s);
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

    // collectors
    std::vector<Mix_Chunk*> mCopperMiner;
    std::vector<Mix_Chunk*> mSilverMiner;
    std::vector<Mix_Chunk*> mTreeCutter;
    std::vector<Mix_Chunk*> mStoneCutter;

    // events
    Mix_Chunk* mFire = nullptr;
    Mix_Chunk* mCollapse = nullptr;

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
};

#endif // ESOUNDS_H
