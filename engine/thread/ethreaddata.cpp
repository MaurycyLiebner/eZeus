#include "ethreaddata.h"

#include "engine/egameboard.h"

#include <chrono>

eThreadData::eThreadData(const eThreadData& s) {
    mBoard = s.mBoard;
}

void eThreadData::initialize(const int w, const int h) {
    mBoard.initialize(w, h);
    mTmpBoard.initialize(w, h);
}

void eThreadData::scheduleUpdate(eGameBoard& board) {
//    using std::chrono::high_resolution_clock;
//    using std::chrono::duration_cast;
//    using std::chrono::duration;
//    using std::chrono::milliseconds;

//    const auto t1 = high_resolution_clock::now();

    std::lock_guard l(mTmpBoardMutex);
    mTmpChanged = true;
    for(int i = 0; i < board.width(); i++) {
        for(int j = 0; j < board.height(); j++) {
            const auto src = board.dtile(i, j);
            const auto dst = mTmpBoard.dtile(i, j);
            if(!src || !dst) continue;
            dst->load(src);
        }
    }

//    const auto t2 = high_resolution_clock::now();

//    const duration<double, std::milli> ms = t2 - t1;
//    printf("update board: %f ms\n", ms.count());
}

void eThreadData::updateBoard() {
    if(mTmpChanged) {
        std::lock_guard l(mTmpBoardMutex);
        std::swap(mBoard, mTmpBoard);
        mTmpChanged = false;
    }
}

void eThreadData::setRunning(const bool r) {
    mRunning = r;
}
