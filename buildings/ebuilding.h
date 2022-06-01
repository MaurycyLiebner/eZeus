#ifndef EBUILDING_H
#define EBUILDING_H

#include "pointers/eobject.h"

#include "eoverlay.h"
#include "etexturecollection.h"
#include "widgets/etilepainter.h"
#include "engine/emovedirection.h"
#include "engine/eprovide.h"

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

    stadium,

    fountain,
    hospital,

    goat,
    sheep,

    oliveTree,
    vine,
    orangeTree,

    wheatFarm,
    carrotsFarm,
    onionsFarm,

    huntingLodge,
    fishery,
    urchinQuay,
    cardingShed,
    dairy,
    growersLodge,
    orangeTendersLodge,

    granary,
    warehouse,

    foodVendor,
    fleeceVendor,
    oilVendor,
    wineVendor,
    armsVendor,
    horseTrainer,

    timberMill,
    masonryShop,
    mint,
    foundry,

    olivePress,
    winery,
    sculptureStudio,
    artisansGuild,

    wall,
    tower,
    gatehouse,

    triremeWharf,
    horseRanch,
    armory,

    maintenanceOffice,
    taxOffice,
    watchPost,

    palace,

    park,
    doricColumn,
    ionicColumn,
    corinthianColumn,
    avenue,

    commemorative,

    bench,
    flowerGarden,
    gazebo,
    hedgeMaze,
    fishPond,

    waterPark,

    birdBath,
    shortObelisk,
    tallObelisk,
    shellGarden,
    sundial,
    dolphinSculpture,
    spring,
    topiary,
    baths,
    stoneCircle,

    ruins,

    templeAphrodite,
    templeArtemis,
    templeHephaestus,
    templeZeus,

    temple,
    templeTile,
    templeStatue,
    templeMonument,
    templeAltar,

    road
};

class eBuilding : public eObject {
public:
    eBuilding(eGameBoard& board,
              const eBuildingType type,
              const int sw, const int sh);
    virtual ~eBuilding();

    virtual std::shared_ptr<eTexture>
    getTexture(const eTileSize size) const = 0;
    virtual std::vector<eOverlay>
    getOverlays(const eTileSize size) const {
        (void)size;
        return std::vector<eOverlay>();
    }

    virtual void timeChanged(const int by) { (void)by; }
    virtual void nextMonth() {}

    virtual int provide(const eProvide p, const int n);

    static bool sFlatBuilding(const eBuildingType bt);

    using eTileValidator = std::function<bool(eTile*)>;
    eTile* tileNeighbour(const eMoveDirection o,
                         const eTileValidator& v) const;
    eTile* road(const eMoveDirection o) const;

    int seed() const { return mSeed; }
    void setSeed(const int s) { mSeed = s; }
    eBuildingType type() const { return mType; }
    int spanW() const { return mSpanW; }
    int spanH() const { return mSpanH; }

    void incTime(const int by);
    int time() const { return mTime; }
    int textureTime() const { return mTextureTime/4; }

    void addUnderBuilding(eTile* const t);

    void erase();
    void collapse();
    void catchOnFire();
    void putOutFire();
    bool spreadFire();

    bool isOnFire();

    const std::vector<eTile*>& tilesUnder() const {
        return mUnderBuilding;
    }

    void setTileRect(const SDL_Rect& rect) { mTileRect = rect; }
    const SDL_Rect& tileRect() const { return mTileRect; }

    eTile* centerTile() const;

    bool enabled() const { return mEnabled; }
    void setEnabled(const bool e);

    void setOverlayEnabledFunc(const std::function<bool()>& e);
    bool overlayEnabled() const { return mOverlayEnabled(); }

    int maintenance() const { return mMaintance; }

    int playerId() const { return mPlayerId; }

    bool defend(const double a);
    bool dead() const;
private:
    std::vector<eTile*> mUnderBuilding;
    SDL_Rect mTileRect;

    int mSeed;
    const eBuildingType mType;
    const int mSpanW;
    const int mSpanH;

    int mPlayerId{1}; // 0 - neutral
    double mHp = 10000;

    int mMaintance = 100;

    int mTime = 0;
    int mTextureTime = 0;

    bool mEnabled = false;
    std::function<bool()> mOverlayEnabled = [this]() {
        return mEnabled;
    };
};

#endif // EBUILDING_H
