#include "ereadstream.h"

#include "engine/egameboard.h"
#include "characters/actions/walkable/ewalkableobject.h"
#include "characters/actions/walkable/ehasresourceobject.h"
#include "characters/actions/echaracteraction.h"
#include "characters/actions/egodaction.h"
#include "characters/actions/walkable/eobsticlehandler.h"
#include "characters/actions/epatrolaction.h"

eReadStream::eReadStream(SDL_RWops* const src) :
    mSrc(src) {

}

eTile* eReadStream::readTile(eGameBoard& board) {
    bool valid;
    *this >> valid;
    if(valid) {
        int x;
        *this >> x;
        int y;
        *this >> y;
        return board.tile(x, y);
    } else {
        return nullptr;
    }
}

void eReadStream::readBuilding(eGameBoard* board,
                               const eBuildingFunc& func) {
    int bid;
    *this >> bid;
    addPostFunc([board, func, bid]() {
        const auto b = board->buildingWithIOID(bid);
        func(b);
    });
}

void eReadStream::readCharacter(eGameBoard* board,
                                const eCharFunc& func) {
    int cid;
    *this >> cid;
    addPostFunc([board, func, cid]() {
        const auto b = board->characterWithIOID(cid);
        func(b);
    });
}

void eReadStream::readCharacterAction(eGameBoard* board,
                                      const eCharActFunc& func) {
    int caid;
    *this >> caid;
    addPostFunc([board, func, caid]() {
        const auto b = board->characterActionWithIOID(caid);
        func(b);
    });
}

stdsptr<eWalkableObject> eReadStream::readWalkable() {
    bool valid;
    *this >> valid;
    if(valid) {
        eWalkableObjectType type;
        *this >> type;
        const auto r = eWalkableObject::sCreate(type);
        r->read(*this);
        return r;
    } else {
        return nullptr;
    }
}

stdsptr<eHasResourceObject> eReadStream::readHasResource() {
    bool valid;
    *this >> valid;
    if(valid) {
        eHasResourceObjectType type;
        *this >> type;
        const auto r = eHasResourceObject::sCreate(type);
        r->read(*this);
        return r;
    } else {
        return nullptr;
    }
}

stdsptr<eCharacterActionFunction> eReadStream::readCharActFunc(
        eGameBoard& board) {
    bool hasFinish;
    *this >> hasFinish;
    if(hasFinish) {
        eCharActFuncType type;
        *this >> type;
        const auto f = eCharacterActionFunction::sCreate(board, type);
        f->read(*this);
        return f;
    }
    return nullptr;
}

stdsptr<eGodAct> eReadStream::readGodAct(eGameBoard& board) {
    bool hasFinish;
    *this >> hasFinish;
    if(hasFinish) {
        eGodActType type;
        *this >> type;
        const auto f = eGodAct::sCreate(board, type);
        f->read(*this);
        return f;
    }
    return nullptr;
}

stdsptr<eObsticleHandler> eReadStream::readObsticleHandler(
        eGameBoard& board) {
    bool valid;
    *this >> valid;
    if(valid) {
        eObsticleHandlerType type;
        *this >> type;
        const auto r = eObsticleHandler::sCreate(board, type);
        r->read(*this);
        return r;
    } else {
        return nullptr;
    }
}

stdsptr<eDirectionTimes> eReadStream::readDirectionTimes(
        eGameBoard& board) {
    const auto r = std::make_shared<eDirectionTimes>();
    int n;
    *this >> n;
    for(int i = 0; i < n; i++) {
        const auto tile = readTile(board);
        eDirectionLastUseTime u;
        u.read(*this);
        (*r)[tile] = u;
    }
    return r;
}

void eReadStream::readCity(eGameBoard* board, const eCityFunc& func) {
    return readCity(board->getWorldBoard(), func);
}

void eReadStream::readCity(eWorldBoard* board, const eCityFunc& func) {
    int cid;
    *this >> cid;
    addPostFunc([board, func, cid]() {
        const auto c = board->cityWithIOID(cid);
        func(c);
    });
}

void eReadStream::readBanner(eGameBoard* board, const eBannerFunc& func) {
    int bid;
    *this >> bid;
    addPostFunc([board, func, bid]() {
        const auto b = board->bannerWithIOID(bid);
        func(b);
    });
}

void eReadStream::readSoldierBanner(eGameBoard* board, const eSoldierBannerFunc& func) {
    int bid;
    *this >> bid;
    addPostFunc([board, func, bid]() {
        const auto b = board->soldierBannerWithIOID(bid);
        func(b ? b->ref<eSoldierBanner>() : nullptr);
    });
}

void eReadStream::readGameEvent(eGameBoard* board, const eEventFunc& func) {
    int eid;
    *this >> eid;
    addPostFunc([board, func, eid]() {
        const auto b = board->eventWithIOID(eid);
        func(b);
    });
}

void eReadStream::addPostFunc(const eFunc& func) {
    mPostFuncs.push_back(func);
}

void eReadStream::handlePostFuncs() {
    for(const auto& func : mPostFuncs) {
        func();
    }
    mPostFuncs.clear();
}
