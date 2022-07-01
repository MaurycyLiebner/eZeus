#include "ethreaddata.h"

#include "engine/egameboard.h"

eThreadData::eThreadData(const eThreadData& s) {
    mBoard = s.mBoard;
}

void eThreadData::initialize(const int w, const int h) {
    mBoard.initialize(w, h);
    mTmpBoard.initialize(w, h);
}

void eThreadData::scheduleUpdate(eGameBoard& board) {
    std::lock_guard l(mMutex);
    mTmpChanged = true;
    for(int i = 0; i < board.width(); i++) {
        for(int j = 0; j < board.height(); j++) {
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
        std::swap(mBoard, mTmpBoard);
        mTmpChanged = false;
    }
}

void eThreadData::setRunning(const bool r) {
    mRunning = r;
}
