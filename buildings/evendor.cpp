#include "evendor.h"

#include "characters/echaracter.h"
#include "characters/ecarttransporter.h"
#include "textures/egametextures.h"

eVendor::eVendor(eGameBoard& board,
                 const eResourceType resType,
                 const eProvide provType,
                 const eBaseTex& baseTex,
                 const double overlayX,
                 const double overlayY,
                 const eBaseTex& overlayTex,
                 const eCharGenerator& charGen,
                 const eBuildingType type,
                 const int sw, const int sh,
                 const int maxEmployees) :
    ePatrolBuilding(board,
                    baseTex,
                    0, 0, nullptr,
                    [this]() { return vendorGenerator(); },
                    type, sw, sh,
                    maxEmployees),
    mResType(resType),
    mProvType(provType),
    mCharGen(charGen),
    mOverlayX(overlayX),
    mOverlayY(overlayY),
    mOverlayTex(overlayTex) {

}

eVendor::~eVendor() {
    if(mCart) mCart->kill();
}

std::vector<eOverlay> eVendor::getOverlays(const eTileSize size) const {
    if(mResource <= 0) return {};
    auto os = ePatrolBuilding::getOverlays(size);
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings();
    eOverlay o;
    o.fTex = texs[sizeId].*mOverlayTex;
    o.fX = mOverlayX;
    o.fY = mOverlayY;
    os.push_back(o);
    return os;
}

int eVendor::add(const eResourceType type, const int count) {
    if(!static_cast<bool>(type & mResType)) return 0;

    const int r = std::clamp(count, 0, mMaxResource - mResource);
    mResource += r;
    return r;
}

int eVendor::take(const eResourceType type, const int count) {
    (void)type;
    (void)count;
    return 0;
}

int eVendor::count(const eResourceType type) const {
    if(type != mResType) return 0;
    return mResource;
}

int eVendor::spaceLeft(const eResourceType type) const {
    if(type != mResType) return 0;
    return mMaxResource - mResource;
}

void eVendor::timeChanged(const int by) {
    if(enabled()) {
        if(!mCart) spawnCart(mCart, eCartActionTypeSupport::take);
    }
    ePatrolBuilding::timeChanged(by);
}

stdsptr<eCharacter> eVendor::vendorGenerator() {
    const int mult = 100;
    if(mVendor) {
        mResource += mVendor->provideCount()/mult;
        mVendor.reset();
    }
    if(mResource <= 0) {
        return nullptr;
    }
    mVendor = mCharGen();
    const int take = std::max(mResource, 2);
    mResource -= take;
    mVendor->setProvide(mProvType, mult*take);
    return mVendor;
}
