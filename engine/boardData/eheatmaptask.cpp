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
            if(!t->mainBuildingTile()) continue;
            const auto& ub = t->underBuilding();
            const auto ubt = ub.type();
            const auto a = mHeatGetter(ubt);
            mMap.addHeat(a, ub.tileRect());
        }
    }
}

void eHeatMapTask::finish() {
    if(mFinish) mFinish(mMap);
}
