#include "emissile.h"

#include "engine/egameboard.h"
#include "engine/etile.h"
#include "characters/actions/egodaction.h"

#include "erockmissile.h"
#include "egodmissile.h"
#include "earrowmissile.h"

eMissile::eMissile(eGameBoard& board, const eMissileType type,
                   const std::vector<ePathPoint>& path) :
    mType(type), mBoard(board), mPath(path) {
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
        if(mFinish) mFinish->act();
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

void eMissile::setFinishAction(const stdsptr<eGodAct>& act) {
    mFinish = act;
}

void eMissile::read(eReadStream& src) {
    mPath.read(src);
    src >> mTime;
    src >> mSpeed;
    mFinish = src.readGodAct(mBoard);
    const auto t = src.readTile(mBoard);
    changeTile(t);
}

void eMissile::write(eWriteStream& dst) const {
    mPath.write(dst);
    dst << mTime;
    dst << mSpeed;
    dst.writeGodAct(mFinish.get());
    dst.writeTile(mTile);
}

stdsptr<eMissile> eMissile::sCreate(
        eGameBoard& brd, const eMissileType type) {
    switch(type) {
    case eMissileType::rock:
        return e::make_shared<eRockMissile>(brd);
    case eMissileType::god:
        return e::make_shared<eGodMissile>(brd);
    case eMissileType::arrow:
        return e::make_shared<eArrowMissile>(brd);
    }
    return nullptr;
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
