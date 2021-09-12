#include "egametextures.h"

#include <functional>

bool eGameTextures::sInitialized = false;
std::vector<eTerrainTextures> eGameTextures::sTerrainTextures;
std::vector<eGodTextures> eGameTextures::sGodTextures;
std::vector<eBuildingTextures> eGameTextures::sBuildingTextures;
std::vector<eCharacterTextures> eGameTextures::sCharacterTextures;
std::vector<eInterfaceTextures> eGameTextures::sInterfaceTextures;
std::vector<eDestructionTextures> eGameTextures::sDestructionTextures;

using eLoader = std::function<void(std::string&)>;
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

        gGameLoaders.push_back([i](std::string& text) {
            sTerrainTextures[i].load();
            if(i == 0) {
                text = "Loading small terrain textures...";
            } else if(i == 1) {
                text = "Loading medium terrain textures...";
            } else if(i == 2) {
                text = "Loading large terrain textures...";
            }
        });

        gGameLoaders.push_back([i](std::string& text) {
            sGodTextures[i].load();
            if(i == 0) {
                text = "Loading small god textures...";
            } else if(i == 1) {
                text = "Loading medium god textures...";
            } else if(i == 2) {
                text = "Loading large god textures...";
            }
        });

        gGameLoaders.push_back([i](std::string& text) {
            sBuildingTextures[i].load();
            if(i == 0) {
                text = "Loading small building textures...";
            } else if(i == 1) {
                text = "Loading medium building textures...";
            } else if(i == 2) {
                text = "Loading large building textures...";
            }
        });

        gGameLoaders.push_back([i](std::string& text) {
            sCharacterTextures[i].load();
            if(i == 0) {
                text = "Loading small character textures...";
            } else if(i == 1) {
                text = "Loading medium character textures...";
            } else if(i == 2) {
                text = "Loading large character textures...";
            }
        });

        gGameLoaders.push_back([i](std::string& text) {
            sDestructionTextures[i].load();
            if(i == 0) {
                text = "Loading small destruction textures...";
            } else if(i == 1) {
                text = "Loading medium destruction textures...";
            } else if(i == 2) {
                text = "Loading large destruction textures...";
            }
        });

        gMenuLoaders.push_back([i](std::string& text) {
            sInterfaceTextures[i].load();
            if(i == 0) {
                text = "Loading small interface textures...";
            } else if(i == 1) {
                text = "Loading medium interface textures...";
            } else if(i == 2) {
                text = "Loading large interface textures...";
            }
        });

        i++;
    }

    sInitialized = true;

    return true;
}

bool eGameTextures::loadNextMenu(std::string& text) {
    if(gMenuLoaders.empty()) return true;
    gMenuLoaders.back()(text);
    gMenuLoaders.pop_back();
    return false;
}

int gNextToLoad = 0;

bool eGameTextures::loadNextGame(std::string& text) {
    if(gGameLoaders.empty()) return true;
    gGameLoaders.back()(text);
    gGameLoaders.pop_back();
    return false;
}

int eGameTextures::gameSize() {
    return sTerrainTextures.size() +
           sGodTextures.size() +
           sBuildingTextures.size() +
           sCharacterTextures.size() +
           sDestructionTextures.size();
}

int eGameTextures::menuSize() {
    return sInterfaceTextures.size();
}
