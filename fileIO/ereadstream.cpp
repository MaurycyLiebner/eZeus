#include "ereadstream.h"

#include "engine/egameboard.h"

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

void eReadStream::addPostFunc(const eFunc& func) {
    mPostFuncs.push_back(func);
}

void eReadStream::handlePostFuncs() {
    for(const auto& func : mPostFuncs) {
        func();
    }
    mPostFuncs.clear();
}
