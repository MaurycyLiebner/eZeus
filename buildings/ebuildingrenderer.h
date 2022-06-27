#ifndef EBUILDINGRENDERER_H
#define EBUILDINGRENDERER_H

#include "ebuilding.h"

class eBuildingRenderer : public eObject {
public:
    eBuildingRenderer(const stdsptr<eBuilding>& b);

    virtual std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;
    virtual std::vector<eOverlay>
        getOverlays(const eTileSize size) const;

    virtual int spanW() const;
    virtual int spanH() const;

    virtual bool isMain() const { return true; }

    void draw(eTilePainter& p,
              const double x, const double y,
              const bool erase);
private:
    const stdsptr<eBuilding> mBuilding;
};

#endif // EBUILDINGRENDERER_H
