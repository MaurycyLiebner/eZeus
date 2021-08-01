#ifndef EGAMETEXTURES_H
#define EGAMETEXTURES_H

#include "eterraintextures.h"
#include "edemetertextures.h"
#include "ebuildingtextures.h"
#include "echaractertextures.h"

class eGameTextures {
public:
    static const std::vector<eTerrainTextures>& terrain() {
        return sTerrainTextures;
    }
    static const std::vector<eDemeterTextures>& demeter() {
        return sDemeterTextures;
    }
    static const std::vector<eBuildingTextures>& buildings() {
        return sBuildingTextures;
    }
    static const std::vector<eCharacterTextures>& characters() {
        return sCharacterTextures;
    }

    static bool initialize(SDL_Renderer* const r);
    static bool loadNext(std::string& text);
    static int size();
private:
    static std::vector<eTerrainTextures> sTerrainTextures;
    static std::vector<eDemeterTextures> sDemeterTextures;
    static std::vector<eBuildingTextures> sBuildingTextures;
    static std::vector<eCharacterTextures> sCharacterTextures;
};

#endif // EGAMETEXTURES_H
