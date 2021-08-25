#include "eresourcebuildingbase.h"

#include "characters/actions/ecarttransporteraction.h"

eResourceBuildingBase::eResourceBuildingBase(
        eGameBoard& board,
        const eBuildingType type,
        const int sw, const int sh,
        const eResourceType resType) :
    eBuildingWithResource(board, type, sw, sh),
    mResType(resType) {

}

int eResourceBuildingBase::add(const eResourceType type,
                               const int count) {
    if(type != mResType) return 0;

    const int r = std::clamp(mResource + count, 0, mMaxResource);
    const int result = r - mResource;
    mResource = r;
    return result;
}

int eResourceBuildingBase::take(const eResourceType type,
                                const int count) {
    if(type != mResType) return 0;

    const int result = std::clamp(count, 0, mResource);
    mResource -= result;
    return result;
}

int eResourceBuildingBase::count(const eResourceType type) const {
    if(type != mResType) return 0;
    return mResource;
}

int eResourceBuildingBase::spaceLeft(const eResourceType type) const {
    if(type != mResType) return 0;
    return mMaxResource - mResource;
}

void eResourceBuildingBase::timeChanged() {
    if(!mCart && mResource > 0 && time() > mSpawnTime) {
        mSpawnTime = time() + mWaitTime;
        spawn();
    }
}

bool eResourceBuildingBase::spawn() {
    if(mResource <= 0) return false;
    const int took = take(mResType, 8);
    if(took <= 0) return false;
    mCart = e::make_shared<eCartTransporter>(getBoard());
    mCart->setResource(mResType, took);
    const auto t = tile();
    mCart->changeTile(t);
    const eStdPointer<eResourceBuildingBase> tptr(this);
    const eStdPointer<eCartTransporter> hptr(mCart);
    const auto finishAct = [tptr, this, hptr]() {
        if(hptr) {
            hptr->changeTile(nullptr);
        }
        if(tptr) {
            mCart.reset();
            mSpawnTime = time() + mWaitTime;
        }
    };
    const auto failAct = [this, finishAct, took]() {
        add(mResType, took);
        finishAct();
    };
    const auto a = e::make_shared<eCartTransporterAction>(
                       tileRect(), mCart.get(),
                       eCartActionType::give, mResType,
                       failAct, finishAct);
    mCart->setAction(a);
    return true;
}
