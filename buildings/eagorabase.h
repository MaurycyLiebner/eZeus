#ifndef EAGORABASE_H
#define EAGORABASE_H

#include "buildings/ebuilding.h"

enum class eAgoraOrientation {
    bottomRight,
    topLeft,
    bottomLeft,
    topRight
};

class eAgoraBase : public eBuilding {
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

    eBuilding* building(const int id) const;
    void setBuilding(const int id, const stdsptr<eBuilding>& b);
    void setBuilding(eBuilding* const space, const stdsptr<eBuilding>& b);

    void fillSpaces();
private:
    const int mNPts;
    std::vector<stdsptr<eBuilding>> mBs;
};

#endif // EAGORABASE_H
