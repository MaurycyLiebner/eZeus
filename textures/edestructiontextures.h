#ifndef EDESTRUCTIONTEXTURES_H
#define EDESTRUCTIONTEXTURES_H

#include "etexturecollection.h"

class eDestructionTextures {
public:
    eDestructionTextures(const int tileW, const int tileH,
                         SDL_Renderer* const renderer);

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

    bool fFireLoaded = false;
    void loadFire();

    bool fBlessedLoaded = false;
    void loadBlessed();
    bool fCursedLoaded = false;
    void loadCursed();

    bool fRockLoaded = false;
    void loadRock();
    bool fBlackSpearLoaded = false;
    void loadBlackSpear();
    bool fSpearLoaded = false;
    void loadSpear();
    bool fBlackArrowLoaded = false;
    void loadBlackArrow();
    bool fArrowLoaded = false;
    void loadArrow();

    bool fBlessLoaded = false;
    void loadBless();
    bool fCurseLoaded = false;
    void loadCurse();

    bool fPlagueLoaded = false;
    void loadPlague();

    bool fGodOrangeMissileLoaded = false;
    void loadGodOrangeMissile();
    bool fGodBlueArrowLoaded = false;
    void loadGodBlueArrow();
    bool fGodOrangeArrowLoaded = false;
    void loadGodOrangeArrow();
    bool fMonsterMissileLoaded = false;
    void loadMonsterMissile();
    bool fGodBlueMissileLoaded = false;
    void loadGodBlueMissile();
    bool fGodRedMissileLoaded = false;
    void loadGodRedMissile();
    bool fGodGreenMissileLoaded = false;
    void loadGodGreenMissile();
    bool fGodPinkMissileLoaded = false;
    void loadGodPinkMissile();
    bool fGodPurpleMissileLoaded = false;
    void loadGodPurpleMissile();
    bool fOrichalcMissileLoaded = false;
    void loadOrichalcMissile();

    std::vector<eTextureCollection> fFire;
//    std::vector<eTextureCollection> fBigFire;

    eTextureCollection fBlessed;
    eTextureCollection fCursed;

    eTextureCollection fRock;
    eTextureCollection fBlackSpear;
    eTextureCollection fSpear;
    eTextureCollection fBlackArrow;
    eTextureCollection fArrow;

    eTextureCollection fBless;
    eTextureCollection fCurse;

    eTextureCollection fPlague;

    eTextureCollection fGodOrangeMissile;
    eTextureCollection fGodBlueArrow;
    eTextureCollection fGodOrangeArrow;
    eTextureCollection fMonsterMissile;
    eTextureCollection fGodBlueMissile;
    eTextureCollection fGodRedMissile;
    eTextureCollection fGodGreenMissile;
    eTextureCollection fGodPinkMissile;
    eTextureCollection fGodPurpleMissile;
    eTextureCollection fOrichalcMissile;
};

#endif // EDESTRUCTIONTEXTURES_H
