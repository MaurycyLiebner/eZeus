#ifndef EROAD_H
#define EROAD_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"

class eGatehouse;
class eAgoraBase;

class eRoad : public eBuilding {
public:
    eRoad(eGameBoard& board);

    void erase();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;

    void setUnderAgora(eAgoraBase* const a);
    eAgoraBase* underAgora() const { return mUnderAgora; }

    void setUnderGatehouse(eGatehouse* const g);
    eGatehouse* underGatehouse() const { return mUnderGatehouse; }

    bool isBridge() const;
    bool isRoadblock() const;
    void setRoadblock(const bool rb);

    void bridgeConnectedTiles(std::vector<eTile*>& tiles) const;
private:
    eGatehouse* mUnderGatehouse = nullptr;
    eAgoraBase* mUnderAgora = nullptr;
    bool mRoadblock = false;
};

#endif // EROAD_H
