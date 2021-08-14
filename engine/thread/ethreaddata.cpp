#include "ethreaddata.h"

eThreadData::eThreadData(const eThreadData& s) {
    mBoard = s.mBoard;
    mUpdates = s.mUpdates;
}

void eThreadData::initialize(const int w, const int h) {
    mBoard.initialize(0, 0, w, h);
}

void eThreadData::scheduleUpdate(eGameBoard& board,
                                 const int x, const int y,
                                 const int w, const int h) {
    std::lock_guard l(mMutex);
    auto& dstBoard = mUpdates.emplace_back();
    dstBoard.initialize(x, y, w, h);
    for(int i = x; i < x + w; i++) {
        for(int j = y; j < y + h; j++) {
            const auto src = board.tile(i, j);
            const auto dst = dstBoard.absTile(i, j);
            if(!src || !dst) continue;
            dst->load(src);
        }
    }
}

void eThreadData::updateBoard() {
    std::lock_guard l(mMutex);
    for(auto& u : mUpdates) {
        for(int x = u.x(); x < u.x() + u.width(); x++) {
            for(int y = u.y(); y < u.y() + u.height(); y++) {
                const auto src = u.absTile(x, y);
                const auto dst = mBoard.absTile(x, y);
                if(!src || !dst) continue;
                dst->load(*src);
            }
        }
    }
    mUpdates.clear();
}
