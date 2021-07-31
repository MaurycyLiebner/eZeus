#ifndef EGYMNASIUM_H
#define EGYMNASIUM_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"

class eGymnasium : public eBuilding {
public:
    eGymnasium(std::vector<eBuildingTextures>& texs);

    eTexture getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    using eMovePath = std::vector<std::pair<int, int>>;
    void setMovePath(const eMovePath& path);
private:
    std::vector<eBuildingTextures>& mTextures;
    eMovePath mMovePath;
};

#endif // EGYMNASIUM_H
