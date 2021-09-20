#include "egametextures.h"

#include <functional>

bool eGameTextures::sInitialized = false;
std::vector<eTerrainTextures> eGameTextures::sTerrainTextures;
std::vector<eGodTextures> eGameTextures::sGodTextures;
std::vector<eBuildingTextures> eGameTextures::sBuildingTextures;
std::vector<eCharacterTextures> eGameTextures::sCharacterTextures;
std::vector<eInterfaceTextures> eGameTextures::sInterfaceTextures;
std::vector<eDestructionTextures> eGameTextures::sDestructionTextures;

struct eLoader {
    using eFunc = std::function<void(std::string&)>;
    eLoader(const eFunc& f, const int s) :
        fFunc(f), fSize(s) {}

    eFunc fFunc;
    int fSize;
    bool fFinished = false;
};

std::vector<eLoader> gMenuLoaders;
std::vector<eLoader> gGameLoaders;

bool eGameTextures::initialize(SDL_Renderer* const r) {
    if(sInitialized) return true;
    int i = 0;
    for(const auto& s : {std::pair<int, int>{29, 15},
                         std::pair<int, int>{58, 30},
                         std::pair<int, int>{116, 60}}) {
        sTerrainTextures.emplace_back(s.first, s.second, r);
        sGodTextures.emplace_back(s.first, s.second, r);
        sBuildingTextures.emplace_back(s.first, s.second, r);
        sCharacterTextures.emplace_back(s.first, s.second, r);
        sInterfaceTextures.emplace_back(s.first, s.second, r);
        sDestructionTextures.emplace_back(s.first, s.second, r);

        gGameLoaders.emplace_back([i](std::string& text) {
            sTerrainTextures[i].load();
            if(i == 0) {
                text = "Loading small terrain textures...";
            } else if(i == 1) {
                text = "Loading medium terrain textures...";
            } else if(i == 2) {
                text = "Loading large terrain textures...";
            }
        }, i);

        gGameLoaders.emplace_back([i](std::string& text) {
            sGodTextures[i].load();
            if(i == 0) {
                text = "Loading small god textures...";
            } else if(i == 1) {
                text = "Loading medium god textures...";
            } else if(i == 2) {
                text = "Loading large god textures...";
            }
        }, i);

        gGameLoaders.emplace_back([i](std::string& text) {
            sBuildingTextures[i].load();
            if(i == 0) {
                text = "Loading small building textures...";
            } else if(i == 1) {
                text = "Loading medium building textures...";
            } else if(i == 2) {
                text = "Loading large building textures...";
            }
        }, i);

        gGameLoaders.emplace_back([i](std::string& text) {
            sCharacterTextures[i].load();
            if(i == 0) {
                text = "Loading small character textures...";
            } else if(i == 1) {
                text = "Loading medium character textures...";
            } else if(i == 2) {
                text = "Loading large character textures...";
            }
        }, i);

        gGameLoaders.emplace_back([i](std::string& text) {
            sDestructionTextures[i].load();
            if(i == 0) {
                text = "Loading small destruction textures...";
            } else if(i == 1) {
                text = "Loading medium destruction textures...";
            } else if(i == 2) {
                text = "Loading large destruction textures...";
            }
        }, i);

        gMenuLoaders.emplace_back([i](std::string& text) {
            sInterfaceTextures[i].load();
            if(i == 0) {
                text = "Loading small interface textures...";
            } else if(i == 1) {
                text = "Loading medium interface textures...";
            } else if(i == 2) {
                text = "Loading large interface textures...";
            }
        }, i);

        i++;
    }

    sInitialized = true;

    return true;
}

bool eGameTextures::loadNextMenu(std::string& text) {
    if(gMenuLoaders.empty()) return true;
    gMenuLoaders.back().fFunc(text);
    gMenuLoaders.pop_back();
    return false;
}

int gNextToLoad = 0;

bool eGameTextures::loadNextGame(const eSettings& settings,
                                 std::string& text) {
    const int iMax = gGameLoaders.size();
    for(int i = 0; i < iMax; i++) {
        auto& g = gGameLoaders[i];
        if(g.fFinished) continue;
        if(!settings.fSmallTextures &&
           g.fSize == 0) continue;
        if(!settings.fLargeTextures &&
           g.fSize == 2) continue;
        g.fFunc(text);
        g.fFinished = true;
        return false;
    }
    text = "Finished";
    return true;
}

int eGameTextures::gameSize(const eSettings& settings) {
    int result = 0;
    const int iMax = gGameLoaders.size();
    for(int i = 0; i < iMax; i++) {
        auto& g = gGameLoaders[i];
        if(g.fFinished) continue;
        if(!settings.fSmallTextures &&
           g.fSize == 0) continue;
        if(!settings.fLargeTextures &&
           g.fSize == 2) continue;
        result++;
    }
    return result;
}

int eGameTextures::menuSize() {
    return sInterfaceTextures.size();
}
