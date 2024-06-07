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

    road,

    commonHouse,
    eliteHousing,

    gymnasium,
    college,
    dramaSchool,
    podium,
    theater,

    bibliotheke,
    observatory,
    university,
    laboratory,
    inventorsWorkshop,
    museum,

    stadium,

    fountain,
    hospital,

    goat,
    sheep,
    cattle,

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

    corral,

    granary,
    warehouse,

    tradePost,
    pier,

    commonAgora,
    grandAgora,

    agoraSpace,

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
    horseRanchEnclosure,
    armory,

    maintenanceOffice,
    taxOffice,
    watchPost,

    palace,
    palaceTile,
    bridge,

    park,
    doricColumn,
    ionicColumn,
    corinthianColumn,
    avenue,

    commemorative,
    godMonument,
    godMonumentTile,

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
    orrery,
    spring,
    topiary,
    baths,
    stoneCircle,

    templeAphrodite,
    templeApollo,
    templeAres,
    templeArtemis,
    templeAthena,
    templeAtlas,
    templeDemeter,
    templeDionysus,
    templeHades,
    templeHephaestus,
    templeHera,
    templeHermes,
    templePoseidon,
    templeZeus,

    temple,
    templeTile,
    templeStatue,
    templeMonument,
    templeAltar,

    achillesHall,
    atalantaHall,
    bellerophonHall,
    herculesHall,
    jasonHall,
    odysseusHall,
    perseusHall,
    theseusHall,

    ruins
};

struct eTextureSpace {
    std::shared_ptr<eTexture> fTex;
    bool fOvelays = false;
    SDL_Rect fRect{0, 0, 0, 0};
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

    virtual eTextureSpace
    getTextureSpace(const int tx, const int ty,
                    const eTileSize size) const;

    virtual void timeChanged(const int by) { (void)by; }
    virtual void nextMonth() {}

    virtual int provide(const eProvide p, const int n);

    static bool sWalkableBuilding(const eBuildingType t);
    static bool sFlatBuilding(const eBuildingType bt);
    static bool sSanctuaryBuilding(const eBuildingType bt);
    static bool sAestheticsBuilding(const eBuildingType bt);
    static bool sHeroHall(const eBuildingType bt);
    static bool sFlammable(const eBuildingType bt);
    static bool sTimedBuilding(const eBuildingType bt);
    static bool sBlessable(const eBuildingType bt);
    static bool sAttackable(const eBuildingType bt);

    static std::string sNameForBuilding(eBuilding* const b);
    static std::string sNameForBuilding(const eBuildingType type);
    static void sInfoText(eBuilding* const b,
                          std::string& title,
                          std::string& info,
                          std::string& employmentInfo,
                          std::string& additionalInfo);

    using eTileValidator = std::function<bool(eTile*)>;
    eTile* tileNeighbour(const eMoveDirection o,
                         const eTileValidator& v) const;
    std::vector<eTile*> surroundingRoad(const bool diagonal) const;

    int seed() const { return mSeed; }
    void setSeed(const int s) { mSeed = s; }
    eBuildingType type() const { return mType; }
    int spanW() const { return mSpanW; }
    int spanH() const { return mSpanH; }

    void incTime(const int by);
    int time() const { return mTime; }
    int textureTime() const;
    void setFrameShift(const int f) { mFrameShift = f; }

    void addUnderBuilding(eTile* const t);

    virtual void erase();
    void collapse();

    bool isOnFire();
    void setOnFire(const bool f);

    bool spreadFire();

    const std::vector<eTile*>& tilesUnder() const {
        return mUnderBuilding;
    }

    void setTileRect(const SDL_Rect& rect) { mTileRect = rect; }
    const SDL_Rect& tileRect() const { return mTileRect; }

    void setCenterTile(eTile* const ct);
    eTile* centerTile() const;

    bool enabled() const { return mEnabled; }
    void setEnabled(const bool e);

    void setOverlayEnabledFunc(const std::function<bool()>& e);
    bool overlayEnabled() const { return mOverlayEnabled(); }

    int maintenance() const { return mMaintance; }

    int playerId() const { return mPlayerId; }

    bool defend(const double a);
    bool dead() const;

    std::vector<eTile*> neighbours() const;

    void setBlessed(const double b);
    bool blessed() const { return mBlessed > 0.01; }
    bool cursed() const { return mBlessed < -0.01; }

    virtual void read(eReadStream& src);
    virtual void write(eWriteStream& dst) const;

    void setIOID(const int id);
    int ioID() const { return mIOID; }
private:
    eTile* mCenterTile = nullptr;
    std::vector<eTile*> mUnderBuilding;
    SDL_Rect mTileRect;

    int mIOID = -1;
    int mSeed;
    const eBuildingType mType;
    const int mSpanW;
    const int mSpanH;

    int mPlayerId{1}; // 0 - neutral
    double mHp = 1000;

    int mMaintance = 100;

    bool mOnFire = false;

    int mTime = 0;
    int mFrameShift = rand() % 100;

    bool mEnabled = false;
    std::function<bool()> mOverlayEnabled = [this]() {
        return mEnabled;
    };

    double mBlessed = 0;
    int mBlessTime = 0;
};

#endif // EBUILDING_H
