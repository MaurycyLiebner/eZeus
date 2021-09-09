#include "eresourcecollectbuilding.h"

#include "characters/eresourcecollector.h"
#include "characters/actions/ecollectresourceaction.h"
#include "textures/egametextures.h"

eResourceCollectBuilding::eResourceCollectBuilding(
        eGameBoard& board,
        const eBaseTex baseTex,
        const double overlayX,
        const double overlayY,
        const eOverlays overlays,
        const eCharGenerator& charGen,
        const eBuildingType type,
        const eHasResource& hr,
        const eTranformFunc& tf,
        const int sw, const int sh,
        const int maxEmployees,
        const eResourceType resType) :
    eResourceBuildingBase(board, type, sw, sh, maxEmployees, resType),
    mCharGenerator(charGen),
    mTextures(eGameTextures::buildings()),
    mBaseTex(baseTex), mOverlays(overlays),
    mOverlayX(overlayX), mOverlayY(overlayY),
    mHasRes(hr), mTransFunc(tf) {

}

std::shared_ptr<eTexture> eResourceCollectBuilding::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].*mBaseTex;
}

std::vector<eOverlay> eResourceCollectBuilding::
    getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& coll = mTextures[sizeId].*mOverlays;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = mOverlayX;
    o.fY = mOverlayY;
    if(resource() > 0) {
        const auto texs = mTextures[sizeId];
        const eTextureCollection* coll = nullptr;
        double x = -0.5;
        double y = -2;
        switch(resourceType()) {
        case eResourceType::meat:
            coll = &texs.fWaitingMeat;
            break;
        case eResourceType::cheese:
            coll = &texs.fWaitingCheese;
            break;
        case eResourceType::wheat:
            coll = &texs.fWaitingWheat;
            break;
        case eResourceType::wood:
            coll = &texs.fWaitingWood;
            x += 0.25;
            y += 0.25;
            break;
        case eResourceType::bronze:
            coll = &texs.fWaitingBronze;
            break;
        case eResourceType::grapes:
            coll = &texs.fWaitingGrapes;
            break;
        case eResourceType::olives:
            coll = &texs.fWaitingOlives;
            break;
        case eResourceType::armor:
            coll = &texs.fWaitingArmor;
            break;
        default: break;
        }

        if(coll) {
            const int resMax = coll->size() - 1;
            const int res = std::clamp(resource() - 1, 0, resMax);
            eOverlay resO;
            resO.fTex = coll->getTexture(res);
            resO.fX = x;
            resO.fY = y;

            return std::vector<eOverlay>({o, resO});
        }
    }
    return std::vector<eOverlay>({o});
}

void eResourceCollectBuilding::timeChanged(const int by) {
    eResourceBuildingBase::timeChanged(by);
    if(enabled() && !mCollector && time() > mSpawnTime) {
        spawn();
        mSpawnTime = time() + mWaitTime;
    }
}

bool eResourceCollectBuilding::spawn() {
    if(resource() >= maxResource()) return false;
    const auto t = tile();
    mCollector = mCharGenerator();
    mCollector->changeTile(t);
    const eStdPointer<eResourceCollectBuilding> tptr(this);
    const auto finishAct = [tptr, this]() {
        if(!tptr) return;
        if(mCollector) {
            add(resourceType(), mCollector->collected());
            mCollector->changeTile(nullptr);
            mCollector.reset();
        }
        mSpawnTime = time() + mWaitTime;
    };

    const auto a = e::make_shared<eCollectResourceAction>(
                       tileRect(), mCollector.get(), mHasRes,
                       mTransFunc, finishAct, finishAct);
    mCollector->setAction(a);
    return true;
}
