#ifndef EGATEHOUSERENDERER_H
#define EGATEHOUSERENDERER_H

#include "ebuildingrenderer.h"

class eGatehouse;

enum class eGatehouseRendererType {
    grt1, grt2
};

class eGatehouseRenderer : public eBuildingRenderer {
public:
    eGatehouseRenderer(const bool rotated,
                       const eGatehouseRendererType type,
                       const stdsptr<eGatehouse>& b);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
    std::vector<eOverlay>
        getOverlays(const eTileSize size) const;

    int spanW() const { return 2; }
    int spanH() const { return 2; };

    eGatehouseRendererType gtype() const { return mType; }
private:
    const bool mRotated;
    const eGatehouseRendererType mType;
    const stdsptr<eGatehouse> mBuilding;
};

#endif // EGATEHOUSERENDERER_H
