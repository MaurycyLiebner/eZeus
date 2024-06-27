#ifndef ETRADEPOST_H
#define ETRADEPOST_H

#include "ewarehousebase.h"

#include "engine/eworldcity.h"
#include "ewalkablehelpers.h"

enum class eTradePostType {
    post, pier
};

class eTradePost : public eWarehouseBase {
public:
    eTradePost(eGameBoard& board, eWorldCity& city,
               const eTradePostType type = eTradePostType::post);
    ~eTradePost();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;
    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

    void timeChanged(const int by) override;

    void erase() override;

    void setOrders(const eResourceType imports,
                   const eResourceType exports);

    void getOrders(eResourceType& imports,
                   eResourceType& exports) const;

    eWorldCity& city() const { return mCity; }

    eTile* routeStart() const { return mRouteStart; }
    void updateRouteStart();

    void spawnTrader();

    int buy(const int cash);
    int sell(const int items);

    void setWalkable(const stdsptr<eWalkableObject>& w);
    void setUnpackBuilding(eBuilding* const b);
    void setOrientation(const eOrientation o);
    eOrientation orientation() const;
    eTradePostType tpType() const { return mType; }

    using eCharacterCreator =
        std::function<stdsptr<eCharacter>(eTile*, eGameBoard&)>;
    void setCharacterCreator(const eCharacterCreator& c);

    eBuilding* unpackBuilding() const { return mUnpackBuilding; }

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    bool trades() const;
private:
    eWorldCity& mCity;
    const eTradePostType mType;
    eResourceType mImports = eResourceType::none;
    eResourceType mExports = eResourceType::none;
    eOrientation mO = eOrientation::topLeft;

    eCharacterCreator mCharGen;
    stdsptr<eWalkableObject> mWalkable = eWalkableObject::sCreateDefault();
    eBuilding* mUnpackBuilding = this;

    eTile* mRouteStart = nullptr;

    int mRouteTimer = 0;
};

#endif // ETRADEPOST_H
