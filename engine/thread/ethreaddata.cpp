#include "ethreaddata.h"

#include "engine/egameboard.h"

eThreadData::eThreadData(const eThreadData& s) {
    mBoard = s.mBoard;
}

void eThreadData::initialize(const int w, const int h) {
    mBoard.initialize(w, h);
    mTmpBoard.initialize(w, h);
}

void eThreadData::scheduleUpdate(eGameBoard& board,
                                 const int x, const int y,
                                 const int w, const int h) {
    std::lock_guard l(mMutex);
    mTmpChanged = true;
    for(int i = x; i < x + w; i++) {
        for(int j = y; j < y + h; j++) {
            const auto src = board.dtile(i, j);
            const auto dst = mTmpBoard.dtile(i, j);
            if(!src || !dst) continue;
            dst->load(src);
        }
    }
}

void eThreadData::updateBoard() {
    if(mTmpChanged) {
        std::lock_guard l(mMutex);
        mBoard = mTmpBoard;
        mTmpChanged = false;
    }
}

void eThreadData::setRunning(const bool r) {
    mRunning = r;
}
