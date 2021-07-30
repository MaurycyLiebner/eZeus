#ifndef ESMALLHOUSE_H
#define ESMALLHOUSE_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"

class eSmallHouse : public eBuilding {
public:
    eSmallHouse(std::vector<eBuildingTextures>& texs);

    eTexture getTexture(const eTileSize size) const;

    void levelUp();
    void levelDown();
private:
    void setLevel(const int l);

    int mLevel = 0;
    std::vector<eBuildingTextures>& mTextures;
};

#endif // ESMALLHOUSE_H
