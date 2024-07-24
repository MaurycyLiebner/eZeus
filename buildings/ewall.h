#ifndef EWALL_H
#define EWALL_H

#include "ebuilding.h"

class eWall : public eBuilding {
public:
    eWall(eGameBoard& board);
    ~eWall();

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;

    void setDeleteArchers(const bool d) { mDeleteArchers = d; }
private:
    bool mDeleteArchers = true;
};

#endif // EWALL_H
