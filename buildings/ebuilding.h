#ifndef EBUILDING_H
#define EBUILDING_H

#include "etexturecollection.h"
#include "widgets/etilepainter.h"
#include "engine/etile.h"
#include "engine/emovedirection.h"

class eGameBoard;

enum class eBuildingType {
    none = -1,

    commonHouse,

    gymnasium,
    college,
    dramaSchool,
    podium,
    theater,
    stadium1,
    stadium2,

    fountain,
    hospital,

    oliveTree,
    vine,
    plantation,
    wheat,
    carrots,
    onions,
    huntingLodge,
    fishery,
    urchinQuay,
    cardingShed,
    dairy,
    growersLodge,

    timberMill,
    masonryShop,
    mint,
    foundry,
    artisansGuild,
    olivePress,
    winery,
    sculptureStudio,

    triremeWharf,
    horseRanch,
    armory,

    maintenanceOffice,
    taxOffice,
    watchPost,

    palace1,
    palace2,

    road
};

struct eOverlay {
    double fX;
    double fY;
    eTexture fTex;
};

class eBuilding {
public:
    eBuilding(eGameBoard& board,
              const eBuildingType type,
              const int sw, const int sh);
    virtual ~eBuilding();

    virtual eTexture getTexture(const eTileSize size) const = 0;
    virtual std::vector<eOverlay> getOverlays(const eTileSize size) const {
        (void)size;
        return std::vector<eOverlay>();
    }

    virtual void timeChanged() {}

    using eTileValidator = std::function<bool(eTile*)>;
    eTile* tileNeighbour(const eMoveDirection o,
                         const eTileValidator& v) const;
    eTile* road(const eMoveDirection o) const;

    int seed() const { return mSeed; }
    void setSeed(const int s) { mSeed = s; }
    eBuildingType type() const { return mType; }
    eTile* tile() const { return mTile; }
    int spanW() const { return mSpanW; }
    int spanH() const { return mSpanH; }

    void incTime(const int by);
    int time() const { return mTime; }
    int textureTime() const { return time()/10; }

    void setTile(eTile* const t);

    void draw(eTilePainter& p,
              const double x, const double y,
              const eAlignment align);

    void addUnderBuilding(eTile* const t);
    void erase();

    eGameBoard& getBoard() { return mBoard; }
private:
    std::vector<eTile*> mUnderBuilding;

    eGameBoard& mBoard;
    int mSeed;
    const eBuildingType mType;
    const int mSpanW;
    const int mSpanH;
    int mTime = 0;
    eTile* mTile = nullptr;
};

#endif // EBUILDING_H
