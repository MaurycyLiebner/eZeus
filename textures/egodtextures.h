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

struct eDionysusTextures : public eBasicGodTextures {
    eDionysusTextures(SDL_Renderer* const renderer) :
        eBasicGodTextures(renderer),
        fAppear(renderer) {};


    void load(const std::string& pathBase,
              const int w0, const int w1,
              const int d0, const int d1,
              const int f0, const int f1,
              const int a0, const int a1,
              const eOffsets& offs,
              eTextureLoader& texLoader);

    eTextureCollection fAppear;
};

struct eHermesTextures : public eBasicGodTextures {
    eHermesTextures(SDL_Renderer* const renderer) :
        eBasicGodTextures(renderer) {};


    void load(const std::string& pathBase,
              const int w0, const int w1,
              const int r0, const int r1,
              const int f0, const int f1,
              const eOffsets& offs,
              eTextureLoader& texLoader);

    std::vector<eTextureCollection> fRun;
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

    bool fAphroditeLoaded = false;
    void loadAphrodite();
    bool fApolloLoaded = false;
    void loadApollo();
    bool fAresLoaded = false;
    void loadAres();
    bool fArtemisLoaded = false;
    void loadArtemis();
    bool fAthenaLoaded = false;
    void loadAthena();
    bool fAtlasLoaded = false;
    void loadAtlas();
    bool fDemeterLoaded = false;
    void loadDemeter();
    bool fDionysusLoaded = false;
    void loadDionysus();
    bool fHadesLoaded = false;
    void loadHades();
    bool fHephaestusLoaded = false;
    void loadHephaestus();
    bool fHeraLoaded = false;
    void loadHera();
    bool fHermesLoaded = false;
    void loadHermes();
    bool fPoseidonLoaded = false;
    void loadPoseidon();
    bool fZeusLoaded = false;
    void loadZeus();

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

    eBasicGodTextures fAphrodite;
    eExtendedGodTextures fApollo;
    eBasicGodTextures fAres;
    eExtendedGodTextures fArtemis;
    eExtendedGodTextures fAthena;
    eExtendedGodTextures fAtlas;
    eBasicGodTextures fDemeter;
    eDionysusTextures fDionysus;
    eBasicGodTextures fHades;
    eBasicGodTextures fHephaestus;
    eBasicGodTextures fHera;
    eHermesTextures fHermes;
    eBasicGodTextures fPoseidon;
    eExtendedGodTextures fZeus;
};

#endif // EGODTEXTURES_H
