#ifndef EBUILDING_H
#define EBUILDING_H

#include "pointers/estdselfref.h"

#include "eoverlay.h"
#include "etexturecollection.h"
#include "widgets/etilepainter.h"
#include "engine/emovedirection.h"

class eGameBoard;
class eTile;

enum class eBuildingType {
    none = -1,
    erase,

    commonHouse,
    eliteHousing,

    gymnasium,
    college,
    dramaSchool,
    podium,
    theater,

    stadium1,
    stadium2,

    fountain,
    hospital,

    goat,
    sheep,

    oliveTree,
    vine,

    wheatFarm,
    carrotsFarm,
    onionsFarm,

    huntingLodge,
    fishery,
    urchinQuay,
    cardingShed,
    dairy,
    growersLodge,

    granary,
    warehouse,

    timberMill,
    masonryShop,
    mint,
    foundry,

    olivePress,
    winery,
    sculptureStudio,
    artisansGuild,

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

class eBuilding : public eStdSelfRef {
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
    int textureTime() const { return time()/15; }

    void setTile(eTile* const t);

    void draw(eTilePainter& p,
              const double x, const double y);

    void addUnderBuilding(eTile* const t);
    void erase();

    eGameBoard& getBoard() { return mBoard; }

    const std::vector<eTile*>& tilesUnder() const {
        return mUnderBuilding;
    }

    void setTileRect(const SDL_Rect& rect) { mTileRect = rect; }
    const SDL_Rect& tileRect() const { return mTileRect; }
private:
    std::vector<eTile*> mUnderBuilding;
    SDL_Rect mTileRect;

    eGameBoard& mBoard;
    int mSeed;
    const eBuildingType mType;
    const int mSpanW;
    const int mSpanH;
    int mTime = 0;
    eTile* mTile = nullptr;
};

#endif // EBUILDING_H
