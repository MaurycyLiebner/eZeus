#ifndef EMUSIC_H
#define EMUSIC_H

#include <SDL2/SDL_mixer.h>

#include <vector>
#include <string>

enum class eMusicType {
    none, setup, music, battle
};

class eMusic {
public:
    eMusic();
    ~eMusic();

    static void loadMenu();
    static void load();
    static bool loaded();

    static void incTime();

    static void playMenuMusic();
    static void playRandomMusic();
    static void playRandomBattleMusic();
private:
    void incTimeImpl();

    void playMenuMusicImpl();
    void playRandomMusicImpl();
    void playRandomBattleMusicImpl();

    void loadImpl();
    void loadMenuImpl();
    bool loadSetupMusic(const std::string& path);
    bool loadMusic(const std::string& path);
    bool loadBattleMusic(const std::string& path);
    static eMusic sInstance;

    bool mLoaded{false};
    eMusicType mMusicType{eMusicType::none};

    Mix_Music* mSetupMusic = nullptr;
    std::vector<Mix_Music*> mMusic;
    std::vector<Mix_Music*> mBattleMusic;
};

#endif // EMUSIC_H
