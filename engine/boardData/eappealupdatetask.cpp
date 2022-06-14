#include "eappealupdatetask.h"

#include "../thread/ethreadboard.h"

eAppealUpdateTask::eAppealUpdateTask(const eFunc& finish) :
    mFinish(finish) {

}

void eAppealUpdateTask::run(eThreadBoard& board) {
    const int w = board.width();
    const int h = board.height();
    mMap.initialize(w, h);
    for(int tx = 0; tx < w; tx++) {
        for(int ty = 0; ty < h; ty++) {
            const auto t = board.dtile(tx, ty);
            if(!t->mainBuildingTile()) continue;
            const auto& ub = t->underBuilding();
            const auto ubt = ub.type();
            const auto a = eAppealHelpers::appeal(ubt);
            mMap.addAppeal(a, ub.tileRect());
        }
    }
}

void eAppealUpdateTask::finish() {
    if(mFinish) mFinish(mMap);
}
