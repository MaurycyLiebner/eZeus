#ifndef EAGORABASE_H
#define EAGORABASE_H

#include "buildings/epatrolbuildingbase.h"
#include "engine/eresourcetype.h"

enum class eAgoraOrientation {
    bottomRight,
    topLeft,
    bottomLeft,
    topRight
};

class eAgoraBase : public ePatrolBuildingBase {
public:
    eAgoraBase(eGameBoard& board,
               const eBuildingType type,
               const int sw, const int sh,
               const int nPts);

    virtual SDL_Point pt(const int id) const = 0;

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const {
        (void)size;
        return nullptr;
    }

    void erase();

    SDL_Point pt(const int rx, const int ry,
                 const eAgoraOrientation o,
                 const int id) const;

    eBuilding* building(const int id) const;
    void setBuilding(const int id, const stdsptr<eBuilding>& b);
    void setBuilding(eBuilding* const space, const stdsptr<eBuilding>& b);

    void fillSpaces();

    void agoraProvide(eBuilding* const b);
    int agoraCount(const eProvide r) const;
private:
    const int mNPts;
    std::vector<stdsptr<eBuilding>> mBs;
};

#endif // EAGORABASE_H