#include "einvasionhandler.h"

#include "engine/egameboard.h"

#include "engine/eeventdata.h"

#include "characters/actions/esoldieraction.h"

#include "characters/egreekhoplite.h"
#include "characters/egreekhorseman.h"
#include "characters/egreekrockthrower.h"

#include "characters/etrojanhoplite.h"
#include "characters/etrojanspearthrower.h"
#include "characters/etrojanhorseman.h"

#include "characters/ecentaurhorseman.h"
#include "characters/ecentaurarcher.h"

#include "characters/epersianhoplite.h"
#include "characters/epersianhorseman.h"
#include "characters/epersianarcher.h"

#include "characters/eegyptianhoplite.h"
#include "characters/eegyptianchariot.h"
#include "characters/eegyptianarcher.h"

#include "characters/eatlanteanhoplite.h"
#include "characters/eatlanteanchariot.h"
#include "characters/eatlanteanarcher.h"

#include "characters/emayanhoplite.h"
#include "characters/emayanarcher.h"

#include "characters/eoceanidhoplite.h"
#include "characters/eoceanidspearthrower.h"

#include "characters/ephoenicianhorseman.h"
#include "characters/ephoenicianarcher.h"

#include "characters/eamazon.h"

#include "engine/eevent.h"

#include "etilehelper.h"
#include "buildings/epalace.h"

eInvasionHandler::eInvasionHandler(eGameBoard& board,
                                   const stdsptr<eWorldCity>& city) :
    mBoard(board), mCity(city) {
    board.addInvasionHandler(this);
}

eInvasionHandler::~eInvasionHandler() {
    mBoard.removeInvasionHandler(this);
}

template <typename T>
stdsptr<T> spawnSoldier(eGameBoard& board,
                        eTile* const tile) {
    const auto h = e::make_shared<T>(board);
    h->setPlayerId(2);
    const auto a = e::make_shared<eSoldierAction>(h.get());
    h->setAction(a);
    h->changeTile(tile);
    h->setActionType(eCharacterActionType::walk);
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

    stdsptr<eSoldierBanner> b;
    const auto requestBanner = [&]() {
        if(!b || b->count() >= 8) {
            b = e::make_shared<eSoldierBanner>(
                    eBannerType::enemy, mBoard);
            mBanners.push_back(b);
            solds.push_back(b.get());
            b->setPlayerId(2);
            b->moveTo(tx, ty);
        }
    };

    const auto cType = mCity->type();

    for(int i = 0; i < infantry; i++) {
        stdsptr<eSoldier> s;
        switch(cType) {
        case eWorldCityType::greekCity:
            s = spawnSoldier<eGreekHoplite>(mBoard, tile);
            break;
        case eWorldCityType::trojanCity:
            s = spawnSoldier<eTrojanHoplite>(mBoard, tile);
            break;
        case eWorldCityType::persianCity:
            s = spawnSoldier<ePersianHoplite>(mBoard, tile);
            break;
        case eWorldCityType::centaurCity:
            break;
        case eWorldCityType::amazonCity: {
            const auto a = spawnSoldier<eAmazon>(mBoard, tile);
            a->setIsArcher(false);
            s = a;
        } break;

        case eWorldCityType::egyptianCity:
            s = spawnSoldier<eEgyptianHoplite>(mBoard, tile);
            break;
        case eWorldCityType::mayanCity:
            s = spawnSoldier<eMayanHoplite>(mBoard, tile);
            break;
        case eWorldCityType::phoenicianCity:
            break;
        case eWorldCityType::oceanidCity:
            s = spawnSoldier<eOceanidHoplite>(mBoard, tile);
            break;
        case eWorldCityType::atlanteanCity:
            s = spawnSoldier<eAtlanteanHoplite>(mBoard, tile);
            break;

        default:
            break;
        }
        if(s) {
            requestBanner();
            b->incCount();
            s->setBanner(b.get());
        }
    }
    b.reset();
    for(int i = 0; i < cavalry; i++) {
        stdsptr<eSoldier> s;
        switch(cType) {
        case eWorldCityType::greekCity:
            s = spawnSoldier<eGreekHorseman>(mBoard, tile);
            break;
        case eWorldCityType::trojanCity:
            s = spawnSoldier<eTrojanHorseman>(mBoard, tile);
            break;
        case eWorldCityType::persianCity:
            s = spawnSoldier<ePersianHorseman>(mBoard, tile);
            break;
        case eWorldCityType::centaurCity:
            s = spawnSoldier<eCentaurHorseman>(mBoard, tile);
            break;
        case eWorldCityType::amazonCity:
            break;

        case eWorldCityType::egyptianCity:
            s = spawnSoldier<eEgyptianChariot>(mBoard, tile);
            break;
        case eWorldCityType::mayanCity:
            break;
        case eWorldCityType::phoenicianCity:
            s = spawnSoldier<ePhoenicianHorseman>(mBoard, tile);
            break;
        case eWorldCityType::oceanidCity:
            break;
        case eWorldCityType::atlanteanCity:
            s = spawnSoldier<eAtlanteanChariot>(mBoard, tile);
            break;

        default:
            break;
        }
        if(s) {
            requestBanner();
            b->incCount();
            s->setBanner(b.get());
        }
    }
    b.reset();
    for(int i = 0; i < archers; i++) {
        stdsptr<eSoldier> s;
        switch(cType) {
        case eWorldCityType::greekCity:
            spawnSoldier<eGreekRockThrower>(mBoard, tile);
            break;
        case eWorldCityType::trojanCity:
            s = spawnSoldier<eTrojanSpearthrower>(mBoard, tile);
            break;
        case eWorldCityType::persianCity:
            s = spawnSoldier<ePersianArcher>(mBoard, tile);
            break;
        case eWorldCityType::centaurCity:
            s = spawnSoldier<eCentaurArcher>(mBoard, tile);
            break;
        case eWorldCityType::amazonCity: {
            const auto a = spawnSoldier<eAmazon>(mBoard, tile);
            a->setIsArcher(true);
            s = a;
        } break;

        case eWorldCityType::egyptianCity:
            s = spawnSoldier<eEgyptianArcher>(mBoard, tile);
            break;
        case eWorldCityType::mayanCity:
            s = spawnSoldier<eMayanArcher>(mBoard, tile);
            break;
        case eWorldCityType::phoenicianCity:
            s = spawnSoldier<ePhoenicianArcher>(mBoard, tile);
            break;
        case eWorldCityType::oceanidCity:
            s = spawnSoldier<eOceanidSpearthrower>(mBoard, tile);
            break;
        case eWorldCityType::atlanteanCity:
            s = spawnSoldier<eAtlanteanArcher>(mBoard, tile);
            break;

        default:
            break;
        }
        if(s) {
            requestBanner();
            b->incCount();
            s->setBanner(b.get());
        }
    }

    eSoldierBanner::sPlace(solds, tx, ty, mBoard, 3);
}

void eInvasionHandler::incTime(const int by) {
    std::vector<eSoldierBanner*> solds;
    for(const auto& b : mBanners) {
        solds.push_back(b.get());
        const bool r = b->stationary();
        if(!r) return;
    }
    const int wait = 10000;
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
            eSoldierBanner::sPlace(solds, tx, ty, mBoard, 3);
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
        ed.fCity = mCity;
        if(ss == 0) {
            const bool monn = rand() % 2;
            if(monn) {
                mBoard.allow(eBuildingType::commemorative, 1);
                mBoard.event(eEvent::invasionVictoryMonn, ed);
            } else {
                mBoard.event(eEvent::invasionVictory, ed);
            }
        } else if(p) {
            mStage = eInvasionStage::spread;
        } else {
            mBoard.event(eEvent::invasionDefeat, ed);
            const int tx = mTile->x();
            const int ty = mTile->y();
            eSoldierBanner::sPlace(solds, tx, ty, mBoard, 3);
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

void eInvasionHandler::killAllWithCorpse() {
    mWait = 0;
    for(const auto& b : mBanners) {
        b->killAllWithCorpse();
    }
}
