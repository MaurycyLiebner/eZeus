#ifndef EGAMETEXTURES_H
#define EGAMETEXTURES_H

#include "eterraintextures.h"
#include "edemetertextures.h"
#include "ebuildingtextures.h"
#include "echaractertextures.h"
#include "einterfacetextures.h"
#include "edestructiontextures.h"

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
    static const std::vector<eInterfaceTextures>& interface() {
        return sInterfaceTextures;
    }
    static const std::vector<eDestructionTextures>& destrution() {
        return sDestructionTextures;
    }

    static bool initialize(SDL_Renderer* const r);
    static bool loadNextMenu(std::string& text);
    static bool loadNextGame(std::string& text);
    static int gameSize();
    static int menuSize();
private:
    static bool sInitialized;
    static std::vector<eTerrainTextures> sTerrainTextures;
    static std::vector<eDemeterTextures> sDemeterTextures;
    static std::vector<eBuildingTextures> sBuildingTextures;
    static std::vector<eCharacterTextures> sCharacterTextures;
    static std::vector<eInterfaceTextures> sInterfaceTextures;
    static std::vector<eDestructionTextures> sDestructionTextures;
};

#endif // EGAMETEXTURES_H
