#ifndef EROAD_H
#define EROAD_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"

class eAgoraBase;

class eRoad : public eBuilding {
public:
    eRoad(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;

    void setUnderAgora(eAgoraBase* const a);
    eAgoraBase* underAgora() const { return mUnderAgora; }
private:
    const std::vector<eBuildingTextures>& mTextures;
    eAgoraBase* mUnderAgora = nullptr;
};

#endif // EROAD_H
