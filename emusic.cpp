#include "emusic.h"

eMusic eMusic::sInstance;

eMusic::eMusic() {

}

eMusic::~eMusic() {
    Mix_FreeMusic(mSetupMusic);
    for(const auto m : mMusic) {
        Mix_FreeMusic(m);
    }
    for(const auto m : mBattleMusic) {
        Mix_FreeMusic(m);
    }
}

void eMusic::loadMenu() {
    sInstance.loadMenuImpl();
}

void eMusic::load() {
    sInstance.loadImpl();
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
    mMusicType = eMusicType::setup;
    if(Mix_PlayingMusic()) {
        Mix_FadeOutMusic(1000);
        return;
    }
    if(!mSetupMusic) return;
    Mix_HaltMusic();
    Mix_PlayMusic(mSetupMusic, -1);
}

void eMusic::playRandomMusicImpl() {
    mMusicType = eMusicType::music;
    if(Mix_PlayingMusic()) {
        Mix_FadeOutMusic(1000);
        return;
    }
    if(mMusic.empty()) return;
    Mix_HaltMusic();
    const int id = rand() % mMusic.size();
    Mix_PlayMusic(mMusic[id], 0);
}

void eMusic::playRandomBattleMusicImpl() {
    mMusicType = eMusicType::battle;
    if(Mix_PlayingMusic()) {
        Mix_FadeOutMusic(1000);
        return;
    }
    if(mBattleMusic.empty()) return;
    Mix_HaltMusic();
    const int id = rand() % mBattleMusic.size();
    Mix_PlayMusic(mBattleMusic[id], 0);
}

void eMusic::loadImpl() {
    const std::string dir{"../Audio/Music/"};

    loadMusic(dir + "Afigisi.mp3");
    loadMusic(dir + "Amolfi.mp3");
    loadMusic(dir + "Eilavia.mp3");
    loadMusic(dir + "Eplitha.mp3");
    loadMusic(dir + "Fengari.mp3");
    loadMusic(dir + "Iremos.mp3");
    loadMusic(dir + "Mnimio.mp3");
    loadMusic(dir + "Naoss.mp3");
    loadMusic(dir + "Oyonos.mp3");
    loadMusic(dir + "Perifanos.mp3");
    loadMusic(dir + "Pnevma.mp3");
    loadMusic(dir + "Proi.mp3");

    loadBattleMusic(dir + "Battle1.mp3");
    loadBattleMusic(dir + "Battle2.mp3");
    loadBattleMusic(dir + "Battle3.mp3");
    loadBattleMusic(dir + "Battle4.mp3");
    loadBattleMusic(dir + "Battle_long.mp3");
    loadBattleMusic(dir + "Battle_long2.mp3");
}

void eMusic::loadMenuImpl() {
    const std::string dir{"../Audio/Music/"};

    loadSetupMusic(dir + "Setup.mp3");
}

Mix_Music* loadMusicBase(const std::string& path) {
    const auto music = Mix_LoadMUS(path.c_str());
    if(!music) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return nullptr;
    }
    return music;
}

bool eMusic::loadSetupMusic(const std::string& path) {
    mSetupMusic = loadMusicBase(path);
    return mSetupMusic;
}

bool eMusic::loadMusic(const std::string& path) {
    const auto m = loadMusicBase(path);
    if(!m) return false;
    mMusic.push_back(m);
    return true;
}

bool eMusic::loadBattleMusic(const std::string& path) {
    const auto m = loadMusicBase(path);
    if(!m) return false;
    mBattleMusic.push_back(m);
    return true;
}
