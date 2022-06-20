#ifndef ECOMMONAGORA_H
#define ECOMMONAGORA_H

#include "buildings/ebuilding.h"

enum class eAgoraOrientation {
    bottomRight,
    topLeft,
    bottomLeft,
    topRight
};

class eCommonAgora : public eBuilding {
public:
    eCommonAgora(const eAgoraOrientation o, eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const {
        (void)size;
        return nullptr;
    }

    void erase();

    int nPts() const { return 3; }
    SDL_Point pt(const int id) const;

    eBuilding* building(const int id) const;
    void setBuilding(const int id, const stdsptr<eBuilding>& b);
    void setBuilding(eBuilding* const space, const stdsptr<eBuilding>& b);

    void fillSpaces();
private:
    const eAgoraOrientation mO;
    std::vector<stdsptr<eBuilding>> mBs;
};

#endif // ECOMMONAGORA_H
