#ifndef EROAD_H
#define EROAD_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"

class eAgoraBase;

class eRoad : public eBuilding {
public:
    eRoad(eGameBoard& board);

    void erase();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;

    void setUnderAgora(eAgoraBase* const a);
    eAgoraBase* underAgora() const { return mUnderAgora; }

    bool isBridge() const;

    void bridgeConnectedTiles(std::vector<eTile*>& tiles) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
    eAgoraBase* mUnderAgora = nullptr;
};

#endif // EROAD_H
