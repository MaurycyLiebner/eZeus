#ifndef EGODTEXTURES_H
#define EGODTEXTURES_H

#include "etexturecollection.h"
#include "etextureloadinghelpers.h"

class eTextureLoader;

struct eBasicGodTextures {
    eBasicGodTextures(SDL_Renderer* const renderer) :
        fRenderer(renderer), fDisappear(renderer) {};

    void load(const std::string& pathBase,
              const int w0, const int w1,
              const int d0, const int d1,
              const int f0, const int f1,
              const eOffsets& offs,
              eTextureLoader& texLoader);

    SDL_Renderer* const fRenderer;

    std::vector<eTextureCollection> fWalk;
    eTextureCollection fDisappear;
    std::vector<eTextureCollection> fFight;
};

struct eExtendedGodTextures : public eBasicGodTextures {
    eExtendedGodTextures(SDL_Renderer* const renderer) :
        eBasicGodTextures(renderer) {};


    void load(const std::string& pathBase,
              const int w0, const int w1,
              const int d0, const int d1,
              const int f0, const int f1,
              const int b0, const int b1,
              const eOffsets& offs,
              eTextureLoader& texLoader);

    std::vector<eTextureCollection> fBless;
};

class eGodTextures {
public:
    eGodTextures(const int tileW, const int tileH,
                 SDL_Renderer* const renderer);

    void load();

    void loadAthena(const std::string& baseDir,
                    eTextureLoader& texLoader);
    void loadDemeter(const std::string& baseDir,
                     eTextureLoader& texLoader);
    void loadHades(const std::string& baseDir,
                   eTextureLoader& texLoader);

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

    eExtendedGodTextures fAthena;
    eBasicGodTextures fDemeter;
    eBasicGodTextures fHades;
};

#endif // EGODTEXTURES_H
