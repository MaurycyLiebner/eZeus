#include "emusic.h"

#include "egamedir.h"

eMusic eMusic::sInstance;

eMusic::eMusic() {}

void eMusic::loadMenu() {
    sInstance.loadMenuImpl();
}

void eMusic::load() {
    sInstance.loadImpl();
}

bool eMusic::loaded() {
    return sInstance.mLoaded;
}

void eMusic::incTime() {
    sInstance.incTimeImpl();
}

void eMusic::playMenuMusic() {
    sInstance.playMenuMusicImpl();
}

void eMusic::playRandomMusic() {
    sInstance.playRandomMusicImpl();
}

void eMusic::playRandomBattleMusic() {
    sInstance.playRandomBattleMusicImpl();
}

void eMusic::playMissionIntroMusic() {
    sInstance.playMissionIntroMusicImpl();
}

void eMusic::playMissionVictoryMusic() {
    sInstance.playMissionVictoryMusicImpl();
}

void eMusic::playCampaignVictoryMusic() {
    sInstance.playCampaignVictoryMusicImpl();
}

void eMusic::incTimeImpl() {
    if(Mix_PlayingMusic()) return;
    switch(mMusicType) {
    case eMusicType::none:
        break;
    case eMusicType::setup:
        playMenuMusicImpl();
        break;
    case eMusicType::music:
        playRandomMusicImpl();
        break;
    case eMusicType::battle:
        playRandomBattleMusicImpl();
        break;
    }
}

void eMusic::playMenuMusicImpl() {
    const bool change = mMusicType != eMusicType::setup;
    mMusicType = eMusicType::setup;
    if(Mix_PlayingMusic()) {
        if(!change) return;
        Mix_FadeOutMusic(1000);
        return;
    }
    Mix_HaltMusic();
    mSetupMusic->playRandomSound(true);
}

void eMusic::playRandomMusicImpl() {
    const bool change = mMusicType != eMusicType::music;
    mMusicType = eMusicType::music;
    if(Mix_PlayingMusic()) {
        if(!change) return;
        Mix_FadeOutMusic(1000);
        return;
    }
    Mix_HaltMusic();
    mMusic->playRandomSound();
}

void eMusic::playRandomBattleMusicImpl() {
    const bool change = mMusicType != eMusicType::battle;
    mMusicType = eMusicType::battle;
    if(Mix_PlayingMusic()) {
        if(!change) return;
        Mix_FadeOutMusic(1000);
        return;
    }
    Mix_HaltMusic();
    mBattleMusic->playRandomSound();
}

void eMusic::playMissionIntroMusicImpl() {
    Mix_HaltMusic();
    mMissionIntro.playRandomSound();
}

void eMusic::playMissionVictoryMusicImpl() {
    Mix_HaltMusic();
    mMissionVictory.playRandomSound();
}

void eMusic::playCampaignVictoryMusicImpl() {
    Mix_HaltMusic();
    mCampaignVictory.playRandomSound();
}

void eMusic::loadImpl() {
    if(mLoaded) return;
    mLoaded = true;
    const std::string dir{eGameDir::path("Audio/Music/")};

    mMusic->addPath(dir + "Afigisi.mp3");
    mMusic->addPath(dir + "Amolfi.mp3");
    mMusic->addPath(dir + "Eilavia.mp3");
    mMusic->addPath(dir + "Eplitha.mp3");
    mMusic->addPath(dir + "Fengari.mp3");
    mMusic->addPath(dir + "Iremos.mp3");
    mMusic->addPath(dir + "Mnimio.mp3");
    mMusic->addPath(dir + "Naoss.mp3");
    mMusic->addPath(dir + "Oyonos.mp3");
    mMusic->addPath(dir + "Perifanos.mp3");
    mMusic->addPath(dir + "Pnevma.mp3");
    mMusic->addPath(dir + "Proi.mp3");

    mBattleMusic->addPath(dir + "Battle1.mp3");
    mBattleMusic->addPath(dir + "Battle2.mp3");
    mBattleMusic->addPath(dir + "Battle3.mp3");
    mBattleMusic->addPath(dir + "Battle4.mp3");
    mBattleMusic->addPath(dir + "Battle_long.mp3");
    mBattleMusic->addPath(dir + "Battle_long2.mp3");

    mMissionVictory.addPath(dir + "mission_victory.wav");
    mCampaignVictory.addPath(dir + "campaign_victory.wav");
}

void eMusic::loadMenuImpl() {
    if(mMenuLoaded) return;
    mMenuLoaded = true;
    const std::string dir{eGameDir::path("Audio/Music/")};
    mSetupMusic->addPath(dir + "Setup.mp3");
    mMissionIntro.addPath(dir + "mission_intro.wav");
}
