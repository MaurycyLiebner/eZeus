#include "einvasionhandler.h"

#include "characters/actions/esoldieraction.h"
#include "characters/egreekrockthrower.h"
#include "characters/egreekhoplite.h"
#include "characters/egreekhorseman.h"

#include "etilehelper.h"
#include "buildings/epalace.h"

eInvasionHandler::eInvasionHandler(eGameBoard& board,
                                   const stdsptr<eWorldCity>& city) :
    mBoard(board), mCity(city) {
    board.addInvasion(this);
}

eInvasionHandler::~eInvasionHandler() {
    mBoard.removeInvasion(this);
}

template <typename T>
stdsptr<eSoldier> spawnSoldier(eGameBoard& board,
                               eTile* const tile,
                               eSoldierBanner* const b) {
    const auto h = e::make_shared<T>(board);
    h->setPlayerId(2);
    const auto a = e::make_shared<eSoldierAction>(h.get());
    h->setAction(a);
    h->changeTile(tile);
    h->setActionType(eCharacterActionType::walk);
    h->setBanner(b);
    return h;
}

void eInvasionHandler::initialize(eTile* const tile,
                                  const int infantry,
                                  const int cavalry,
                                  const int archers) {
    mTile = tile;

    const int tx = tile->x();
    const int ty = tile->y();

    std::vector<eSoldierBanner*> solds;

    if(infantry > 0) {
        const auto b = e::make_shared<eSoldierBanner>(eBannerType::hoplite,
                                                      mBoard);
        mBanners.push_back(b);
        solds.push_back(b.get());
        b->setPlayerId(2);
        b->moveTo(tx, ty);
        for(int i = 0; i < infantry; i++) {
            spawnSoldier<eGreekHoplite>(mBoard, tile, b.get());
        }
    }
    if(cavalry > 0) {
        const auto b = e::make_shared<eSoldierBanner>(eBannerType::horseman,
                                                      mBoard);
        mBanners.push_back(b);
        solds.push_back(b.get());
        b->setPlayerId(2);
        b->moveTo(tx, ty);
        for(int i = 0; i < cavalry; i++) {
            spawnSoldier<eGreekHorseman>(mBoard, tile, b.get());
        }
    }
    if(archers > 0) {
        const auto b = e::make_shared<eSoldierBanner>(eBannerType::rockThrower,
                                                      mBoard);
        mBanners.push_back(b);
        solds.push_back(b.get());
        b->setPlayerId(2);
        b->moveTo(tx, ty);
        for(int i = 0; i < archers; i++) {
            spawnSoldier<eGreekRockThrower>(mBoard, tile, b.get());
        }
    }

    eSoldierBanner::sPlace(solds, tx, ty, mBoard, 5);
}

void eInvasionHandler::incTime(const int by) {
    std::vector<eSoldierBanner*> solds;
    for(const auto& b : mBanners) {
        solds.push_back(b.get());
        const bool r = b->stationary();
        if(!r) return;
    }
    const int wait = 2500;
    mWait += by;
    if(mWait < wait) return;
    mWait -= wait;
    switch(mStage) {
    case eInvasionStage::spread: {
        mStage = eInvasionStage::invade;
        const auto p = mBoard.palace();
        if(p) {
            const auto t = p->centerTile();
            for(const auto& b : mBanners) {
                b->moveTo(t->x(), t->y());
            }
        } else {
            const int dtx = mBoard.width()/2;
            const int dty = mBoard.height()/2;
            int tx;
            int ty;
            eTileHelper::dtileIdToTileId(dtx, dty, tx, ty);
            eSoldierBanner::sPlace(solds, tx, ty, mBoard, 5);
        }
    } break;
    case eInvasionStage::invade: {
        mStage = eInvasionStage::comeback;
        const auto p = mBoard.palace();
        int ss = 0;
        for(const auto& b : mBanners) {
            ss += b->count();
        }
        eEventData ed;
        ed.fCity = mCity.get();
        if(ss == 0) {
            mBoard.event(eEvent::invasionVictory, ed);
        } else if(p) {
            mStage = eInvasionStage::spread;
        } else {
            mBoard.event(eEvent::invasionDefeat, ed);
            const int tx = mTile->x();
            const int ty = mTile->y();
            eSoldierBanner::sPlace(solds, tx, ty, mBoard, 5);
        }
    } break;
    case eInvasionStage::comeback: {
        for(const auto& b : mBanners) {
            b->killAll();
        }
        delete this;
    } break;
    }
}

void eInvasionHandler::read(eReadStream& src) {
    src.readCity(&mBoard, [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
    mTile = src.readTile(mBoard);
    src >> mStage;

    {
        int nb;
        src >> nb;

        for(int i = 0; i < nb; i++) {
            eBannerType type;
            src >> type;
            const auto b = e::make_shared<eSoldierBanner>(type, mBoard);
            b->read(src);
            mBanners.push_back(b);
        }
    }

    src >> mWait;
}

void eInvasionHandler::write(eWriteStream& dst) const {
    dst.writeCity(mCity.get());
    dst.writeTile(mTile);
    dst << mStage;

    {
        const int nb = mBanners.size();
        dst << nb;
        for(const auto& b : mBanners) {
            dst << b->type();
            b->write(dst);
        }
    }

    dst << mWait;
}
