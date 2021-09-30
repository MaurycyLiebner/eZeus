#ifndef ETEMPLERENDERER_H
#define ETEMPLERENDERER_H

#include "../ebuildingrenderer.h"
#include "etemplebuilding.h"

class eTempleRenderer : public eBuildingRenderer {
public:
    eTempleRenderer(const int id,
                    const stdsptr<eTempleBuilding>& b);


    std::shared_ptr<eTexture>
    getTexture(const eTileSize size) const;

    std::vector<eOverlay>
    getOverlays(const eTileSize size) const;
private:
    const int mId;
    const stdsptr<eTempleBuilding> mB;
};

#endif // ETEMPLERENDERER_H
