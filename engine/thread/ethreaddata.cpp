#include "ethreaddata.h"

void eThreadData::initialize(const int w, const int h) {
    std::lock_guard l(mDataMutex);
    mBoard.initialize(0, 0, w, h);
    const int dataDim = 50;
    const int nW = ceil(double(w)/dataDim);
    const int nH = ceil(double(h)/dataDim);
    for(int i = 0; i < nW; i++) {
        const int dw = std::min(dataDim, w - i*dataDim);
        auto& yArr = mData.emplace_back();
        for(int j = 0; j < nH; j++) {
            auto& y = yArr.emplace_back();
            const int dh = std::min(dataDim, h - j*dataDim);
            y.initialize(i*dataDim, j*dataDim, dw, dh);
        }
    }
}

void eThreadData::updateBoard() {
    std::lock_guard l(mDataMutex);
    for(auto& dd : mData) {
        for(auto& d : dd) {
            if(!d.changed()) continue;
            const int xx = d.x();
            const int yy = d.y();
            const int iMax = xx + d.width();
            const int jMax = yy + d.height();
            for(int i = xx; i < iMax; i++) {
                for(int j = yy; j < jMax; j++) {
                    const auto dst = mBoard.absTile(i, j);
                    const auto src = d.absTile(i, j);
                    dst->load(*src);
                }
            }
            d.setChanged(false);
        }
    }
}
