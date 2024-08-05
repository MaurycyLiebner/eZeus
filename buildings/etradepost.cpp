#include "etradepost.h"

#include "textures/egametextures.h"

#include "engine/egameboard.h"

#include "epathfindtask.h"
#include "ewalkablehelpers.h"

#include "characters/etrader.h"
#include "characters/actions/etraderaction.h"
#include "characters/etradeboat.h"
#include "enumbers.h"

eTradePost::eTradePost(eGameBoard& board, eWorldCity& city,
                       const eTradePostType type) :
    eWarehouseBase(board, eBuildingType::tradePost, 4, 4, 24,
                   eResourceType::tradePost, 15),
    mCity(city), mType(type) {
    eGameTextures::loadTradingPost();
    setOverlayEnabledFunc([]() { return true; });
    setOrders(eResourceType::none, eResourceType::none);
    getBoard().registerTradePost(this);

    switch(type) {
    case eTradePostType::pier: {
        setCharacterCreator([](eTile* const tile, eGameBoard& board) {
            const auto r = e::make_shared<eTradeBoat>(board);
            r->changeTile(tile);
            return r;
        });
        setWalkable(eWalkableObject::sCreate(eWalkableObjectType::deepWater));;
    } break;
    case eTradePostType::post: {
        setCharacterCreator([](eTile* const tile, eGameBoard& board) {
            const auto r = e::make_shared<eTrader>(board);
            r->changeTile(tile);
            r->createFollowers();
            return r;
        });
    } break;
    }
}

eTradePost::~eTradePost() {
    getBoard().unregisterTradePost(this);
}

std::shared_ptr<eTexture> eTradePost::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto& coll = blds[sizeId];
    switch(mType) {
    case eTradePostType::post:
        return coll.fTradingPost;
    default:
        return coll.fPier2;
    }

}

std::vector<eOverlay> eTradePost::getOverlays(const eTileSize size) const {
    std::vector<eOverlay> os;
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto& texs = blds[sizeId];
    if(enabled()) {
        const auto& coll = texs.fTradingPostOverlay;
        const int texId = textureTime() % coll.size();
        auto& o = os.emplace_back();
        o.fTex = coll.getTexture(texId);
        switch(mType) {
        case eTradePostType::post:
            o.fX = -3.1;
            o.fY = -7.2;
            break;
        default:
            o.fX = -1.75;
            o.fY = -5.85;
            break;
        }
    }
    const eXY xy = {{-1.5, -3.5},
                    {-1.5, -2.5},
                    {-1.5, -1.5},

                    {-0.5, -4.5},
                    {-0.5, -3.5},
                    {-0.5, -2.5},
                    {-0.5, -1.5},

                    {0.5, -4.5},
                    {0.5, -3.5},
                    {0.5, -2.5},
                    {0.5, -1.5},

                    {1.5, -4.5},
                    {1.5, -3.5},
                    {1.5, -2.5},
                    {1.5, -1.5}};

    getSpaceOverlays(size, os, xy);

    return os;
}

void eTradePost::timeChanged(const int by) {
    mRouteTimer += by;
    if(mRouteTimer > eNumbers::sTraderSpawnPeriod) {
        mRouteTimer = 0;
        if(trades()) spawnTrader();
    }
    eWarehouseBase::timeChanged(by);
}

void eTradePost::erase() {
    if(mUnpackBuilding) {
        mUnpackBuilding->eBuilding::erase();
    }
    eBuilding::erase();
}

void eTradePost::setOrders(const eResourceType imports,
                           const eResourceType exports) {
    mImports = imports;
    mExports = exports;

    eStorageBuilding::setOrders(mExports, mImports, eResourceType::none);
}

void eTradePost::getOrders(eResourceType& imports,
                           eResourceType& exports) const {
    imports = mImports;
    exports = mExports;
}

void eTradePost::updateRouteStart() {
    auto& brd = getBoard();
    auto& tp = brd.threadPool();

    const auto walkable = eWalkableObject::sCreateRect(
                              mUnpackBuilding, mWalkable);

    const auto t = mUnpackBuilding->centerTile();
    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.tile(tx, ty);
    };

    const auto finalTile = std::make_shared<std::pair<int, int>>();

    const auto final = [finalTile, walkable](eTileBase* const t) {
        if(!walkable->walkable(t)) return false;
        *finalTile = {t->x(), t->y()};
        if(!t->topRight()) return true;
        if(!t->bottomRight()) return true;
        if(!t->bottomLeft()) return true;
        if(!t->topLeft()) return true;
        return false;
    };

    stdptr<eTradePost> tptr(this);

    const auto finishFunc = [tptr, this, finalTile](
                            std::vector<eOrientation>) {
        if(!tptr) return;
        const int tx = finalTile->first;
        const int ty = finalTile->second;
        mRouteStart = getBoard().tile(tx, ty);
        if(trades()) spawnTrader();
    };

    const auto findFailFunc = [tptr, this]() {
        if(!tptr) return;
        mRouteStart = nullptr;
    };

    const auto pft = new ePathFindTask(startTile, walkable,
                                       final, finishFunc,
                                       findFailFunc, true,
                                       10000);
    tp.queueTask(pft);
}

void eTradePost::spawnTrader() {
    if(!mRouteStart) return updateRouteStart();
    auto& board = getBoard();

    const auto r = mCharGen(mRouteStart, board);

    const auto ta = e::make_shared<eTraderAction>(r.get());
    ta->setFinishOnComeback(true);
    ta->setTradePost(this);
    ta->setUnpackBuilding(mUnpackBuilding);
    ta->setWalkable(eWalkableObject::sCreateRect(
                        mUnpackBuilding, mWalkable));
    r->setAction(ta);
}

int eTradePost::buy(const int cash) {
    if(!trades()) return 0;
    int spent = 0;
    for(auto& b : mCity.buys()) {
        const auto expt = mExports & b.fType;
        const bool exp = static_cast<bool>(expt);
        if(!exp) continue;
        if(b.fUsed >= b.fMax) continue;
        if(b.fPrice > cash) continue;
        const int c = count(b.fType);
        if(c <= 0) continue;
        take(b.fType, 1);
        b.fUsed++;
        spent += b.fPrice;
    }
    auto& brd = getBoard();
    brd.incDrachmas(spent);
    return spent;
}

int eTradePost::sell(const int items) {
    if(!trades()) return 0;
    int earned = 0;
    for(auto& b : mCity.sells()) {
        const auto impt = mImports & b.fType;
        const bool imp = static_cast<bool>(impt);
        if(!imp) continue;
        if(b.fUsed >= b.fMax) continue;
        if(b.fPrice > items) continue;
        const int c = spaceLeftDontAccept(b.fType);
        if(c <= 0) continue;
        addNotAccept(b.fType, 1);
        b.fUsed++;
        earned += b.fPrice;
    }
    auto& brd = getBoard();
    brd.incDrachmas(-earned);
    return earned;
}

void eTradePost::setWalkable(const stdsptr<eWalkableObject>& w) {
    mWalkable = w;
}

void eTradePost::setUnpackBuilding(eBuilding* const b) {
    mUnpackBuilding = b;
}

void eTradePost::setOrientation(const eOrientation o) {
    mO = o;
}

eOrientation eTradePost::orientation() const {
    return mO;
}

void eTradePost::setCharacterCreator(const eCharacterCreator& c) {
    mCharGen = c;
}

void eTradePost::read(eReadStream& src) {
    eStorageBuilding::read(src);

    src >> mImports;
    src >> mExports;
    src >> mRouteTimer;
}

void eTradePost::write(eWriteStream& dst) const {
    eStorageBuilding::write(dst);

    dst << mImports;
    dst << mExports;
    dst << mRouteTimer;
}

bool eTradePost::trades() const {
    if(!mCity.trades()) return false;
    auto& board = getBoard();
    if(mType == eTradePostType::pier) {
        return !board.seaTradeShutdown();
    } else {
        return !board.landTradeShutdown();
    }
}
