#ifndef EMUSIC_H
#define EMUSIC_H

#include "emusicvector.h"

#include <memory>

enum class eMusicType {
    none, setup, music, battle
};

class eMusic {
public:
    eMusic();

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
    static eMusic sInstance;

    bool mLoaded{false};
    bool mMenuLoaded{false};
    eMusicType mMusicType{eMusicType::none};

    std::shared_ptr<eMusicVector> mSetupMusic = std::make_shared<eMusicVector>();
    std::shared_ptr<eMusicVector> mMusic = std::make_shared<eMusicVector>();
    std::shared_ptr<eMusicVector> mBattleMusic = std::make_shared<eMusicVector>();
};

#endif // EMUSIC_H
