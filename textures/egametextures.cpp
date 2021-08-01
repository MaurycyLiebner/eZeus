#include "egametextures.h"

std::vector<eTerrainTextures> eGameTextures::sTerrainTextures;
std::vector<eDemeterTextures> eGameTextures::sDemeterTextures;
std::vector<eBuildingTextures> eGameTextures::sBuildingTextures;
std::vector<eCharacterTextures> eGameTextures::sCharacterTextures;

bool eGameTextures::initialize(SDL_Renderer* const r) {
    for(const auto& s : {std::pair<int, int>{29, 15},
                         std::pair<int, int>{58, 30},
                         std::pair<int, int>{116, 60}}) {
        sTerrainTextures.emplace_back(s.first, s.second, r);
        sDemeterTextures.emplace_back(s.first, s.second, r);
        sBuildingTextures.emplace_back(s.first, s.second, r);
        sCharacterTextures.emplace_back(s.first, s.second, r);
    }

    return true;
}

int gNextToLoad = 0;

bool eGameTextures::loadNext(std::string& text) {
    if(gNextToLoad >= size()) {
        return true;
    } else {
        const int toLoad = gNextToLoad++;
        if(toLoad <= 2) {
            if(toLoad == 0) {
                text = "Loading small terrain textures...";
            } else if(toLoad == 1) {
                text = "Loading medium terrain textures...";
            } else if(toLoad == 2) {
                text = "Loading large terrain textures...";
            }
            sTerrainTextures[toLoad].load();
        } else if(toLoad <= 5) {
            const int dload = toLoad - 3;
            if(dload == 0) {
                text = "Loading small Demeter textures...";
            } else if(dload == 1) {
                text = "Loading medium Demeter textures...";
            } else if(dload == 2) {
                text = "Loading large Demeter textures...";
            }
            sDemeterTextures[dload].load();
        } else if(toLoad <= 8) {
            const int dload = toLoad - 6;
            if(dload == 0) {
                text = "Loading small building textures...";
            } else if(dload == 1) {
                text = "Loading medium building textures...";
            } else if(dload == 2) {
                text = "Loading large building textures...";
            }
            sBuildingTextures[dload].load();
        } else if(toLoad <= 11) {
            const int dload = toLoad - 9;
            if(dload == 0) {
                text = "Loading small character textures...";
            } else if(dload == 1) {
                text = "Loading medium character textures...";
            } else if(dload == 2) {
                text = "Loading large character textures...";
            }
            sCharacterTextures[dload].load();
        }
    }
    return false;
}

int eGameTextures::size() {
    return sTerrainTextures.size() +
           sDemeterTextures.size() +
           sBuildingTextures.size() +
           sCharacterTextures.size();
}
