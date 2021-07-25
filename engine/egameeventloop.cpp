#include "egameeventloop.h"

eGameEventLoop::eGameEventLoop() :
    eEventLoop(24, [this]() { loop(); }) {

}

void eGameEventLoop::initialize(const int w, const int h) {
    const std::lock_guard<std::mutex> l(mBoardMtx);
    mBoard.initialize(w, h);
}

eGameBoard eGameEventLoop::requestBoard() {
    const std::lock_guard<std::mutex> l(mBoardMtx);
    return mBoard;
}

void eGameEventLoop::loop() {

}
