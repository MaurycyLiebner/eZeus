#ifndef EBUILDINGRENDERER_H
#define EBUILDINGRENDERER_H

#include "ebuilding.h"

enum class eBuildingRendererType {
    basic,
    eliteHousing,
    gatehouse,
    palace1,
    palace2,
    stadium1,
    stadium2,
    stairs,
    temple
};

class eBuildingRenderer : public eObject {
public:
    eBuildingRenderer(const stdsptr<eBuilding>& b,
                      const eBuildingRendererType type =
                        eBuildingRendererType::basic);
    ~eBuildingRenderer();

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

    eBuildingRendererType type() const { return mType; }

    void setTile(eTile* const tile);
    eTile* tile() const { return mTile; }
private:
    const stdsptr<eBuilding> mBuilding;
    const eBuildingRendererType mType;

    eTile* mTile = nullptr;
};

#endif // EBUILDINGRENDERER_H
