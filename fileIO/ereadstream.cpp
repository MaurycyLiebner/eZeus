#include "ereadstream.h"

#include "engine/egameboard.h"
#include "characters/actions/walkable/ewalkableobject.h"
#include "characters/actions/walkable/ehasresourceobject.h"

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

void eReadStream::addPostFunc(const eFunc& func) {
    mPostFuncs.push_back(func);
}

void eReadStream::handlePostFuncs() {
    for(const auto& func : mPostFuncs) {
        func();
    }
    mPostFuncs.clear();
}
