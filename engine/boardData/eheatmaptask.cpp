#include "eheatmaptask.h"

#include "../thread/ethreadboard.h"

eHeatMapTask::eHeatMapTask(const eHeatGetter& heatGetter,
                           const eFunc& finish) :
    mHeatGetter(heatGetter), mFinish(finish) {

}

void eHeatMapTask::run(eThreadBoard& board) {
    const int w = board.width();
    const int h = board.height();
    mMap.initialize(w, h);
    for(int tx = 0; tx < w; tx++) {
        for(int ty = 0; ty < h; ty++) {
            const auto t = board.dtile(tx, ty);
            const auto& ub = t->underBuilding();
            const auto ubt = ub.type();
            if(ubt == eBuildingType::none) continue;
            const auto rect = ub.tileRect();
            const int ttx = t->x();
            const int tty = t->y();
            if(ttx != rect.x || tty != rect.y) continue;
            const auto a = mHeatGetter(ubt);
            mMap.addHeat(a, rect);
        }
    }
}

void eHeatMapTask::finish() {
    if(mFinish) mFinish(mMap);
}
