#ifndef ESTAIRSRENDERER_H
#define ESTAIRSRENDERER_H

#include "../ebuildingrenderer.h"

class eStairsRenderer : public eBuildingRenderer {
public:
    eStairsRenderer(const int id, const stdsptr<eBuilding>& b);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;

    int spanW() const { return 1; }
    int spanH() const { return 1; }

    void updateId(eTile* const tile);

    int id() const { return mId; }
private:
    const int mId = 0;
};

#endif // ESTAIRSRENDERER_H
