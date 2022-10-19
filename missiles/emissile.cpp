#include "emissile.h"

#include "engine/egameboard.h"
#include "engine/etile.h"

eMissile::eMissile(eGameBoard& board,
                   const std::vector<ePathPoint>& path) :
    mBoard(board), mPath(path) {
    mBoard.registerMissile(this);
}

eMissile::~eMissile() {
    mBoard.unregisterMissile(this);
}

void eMissile::incTime(const int by) {
    mTime += by;
    if(mPath.finished()) return;
    mPath.progress(0.025*mSpeed*by);
    const auto& pos = mPath.pos();
    const int tx = pos.fX;
    const int ty = pos.fY;
    const auto t = mBoard.tile(tx, ty);
    changeTile(t);
    const bool f = mPath.finished();
    if(f) {
        if(mFinish) mFinish();
        changeTile(nullptr);
    }
}

double eMissile::x() const {
    if(mTile) {
        return mPath.pos().fX - mTile->x();
    } else {
        return mPath.pos().fX;
    }
}

double eMissile::y() const {
    if(mTile) {
        return mPath.pos().fY - mTile->y();
    } else {
        return mPath.pos().fY;
    }
}

void eMissile::setFinishAction(const eAction& a) {
    mFinish = a;
}

void eMissile::changeTile(eTile* const t) {
    if(t != mTile) {
        const auto r = ref<eMissile>();
        if(mTile) {
            mTile->removeMissile(r);
        }
        mTile = t;
        if(mTile) {
            mTile->addMissile(r);
        }
    }
}
