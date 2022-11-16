#include "eresourcecollectbuilding.h"

#include "characters/eresourcecollector.h"
#include "characters/actions/ecollectresourceaction.h"
#include "textures/egametextures.h"
#include "engine/egameboard.h"

eResourceCollectBuilding::eResourceCollectBuilding(
        eGameBoard& board,
        const eBaseTex baseTex,
        const double overlayX,
        const double overlayY,
        const eOverlays overlays,
        const int waitingOO,
        const double waitingOX,
        const double waitingOY,
        const eCharGenerator& charGen,
        const eBuildingType type,
        const stdsptr<eHasResourceObject>& hr,
        const int sw, const int sh,
        const int maxEmployees,
        const eResourceType resType) :
    eResourceCollectBuildingBase(board, type, sw, sh,
                                 maxEmployees, resType),
    mCharGenerator(charGen),
    mTextures(eGameTextures::buildings()),
    mBaseTex(baseTex), mOverlays(overlays),
    mOverlayX(overlayX), mOverlayY(overlayY),
    mWaitingOO(waitingOO),
    mWaitingOX(waitingOX), mWaitingOY(waitingOY),
    mHasRes(hr) {

}

eResourceCollectBuilding::~eResourceCollectBuilding() {
    if(mCollector) mCollector->kill();
}

std::shared_ptr<eTexture> eResourceCollectBuilding::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].*mBaseTex;
}

std::vector<eOverlay> eResourceCollectBuilding::
    getOverlays(const eTileSize size) const {
    std::vector<eOverlay> result;
    const int sizeId = static_cast<int>(size);
    const auto& btexs = eGameTextures::buildings()[sizeId];
    if(mRawCount <= 0) {
        eOverlay& o = result.emplace_back();
        const int wo = seed() % 2;
        const std::vector<eTextureCollection>* coll;
        if(wo) {
            coll = &btexs.fWaitingOverlay0;
        } else {
            coll = &btexs.fWaitingOverlay1;
        }
        const auto& ov = (*coll)[mWaitingOO];
        const int t = textureTime();
        const int id = t % ov.size();
        o.fTex = ov.getTexture(id);
        o.fX = mWaitingOX;
        o.fY = mWaitingOY;
        result.push_back(o);
    } else if(mOverlays) {
        const auto& coll = btexs.*mOverlays;
        const int texId = textureTime() % coll.size();
        eOverlay& o = result.emplace_back();
        o.fTex = coll.getTexture(texId);
        o.fX = mOverlayX;
        o.fY = mOverlayY;
    }
    if(resource() > 0) {
        const auto& texs = mTextures[sizeId];
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
            y -= 0.50;
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
            eOverlay& resO = result.emplace_back();
            resO.fTex = coll->getTexture(res);
            resO.fX = x;
            resO.fY = y;
        }
    }
    return result;
}

void eResourceCollectBuilding::timeChanged(const int by) {
    eResourceBuildingBase::timeChanged(by);
    if(enabled()) {
        if(mRawCount > 0) {
            mProcessTime += by;
            const int wait = mProcessDuration/effectiveness();
            if(mProcessTime > wait) {
                mProcessTime -= wait;
                const auto rt = resourceType();
                if(rt == eResourceType::silver) {
                    auto& brd = getBoard();
                    brd.incDrachmas(25);
                    mRawCount--;
                } else {
                    const int c = eResourceCollectBuilding::add(rt, 1);
                    mRawCount -= c;
                }
                if(mRawCount <= mRawCountCollect) enableSpawn();
            }
        }

        if(!mCollector && mSpawnEnabled) {
            mSpawnTime += by;
            const int wait = mWaitTime/effectiveness();
            if(mSpawnTime > wait) {
                mSpawnTime -= wait;
                spawn();
            }
        }
    }
}

bool eResourceCollectBuilding::spawn() {
    if(resource() >= maxResource()) return false;
    if(!mSpawnEnabled) return false;
    const auto t = centerTile();
    const auto c = mCharGenerator();
    mCollector = c.get();
    c->changeTile(t);

    const auto a = e::make_shared<eCollectResourceAction>(
                       this, c.get(), mHasRes);
    a->setAddResource(mAddResource);
    a->setCollectedAction(mCollectedAction);
    switch(resourceType()) {
    case eResourceType::silver:
    case eResourceType::bronze:
        a->setGetAtTile(false);
    default: break;
    }
    c->setAction(a);
    return true;
}

void eResourceCollectBuilding::addRaw() {
    mRawCount += mRawInc;
    if(mRawCount > mRawCountCollect) disableSpawn();
}

void eResourceCollectBuilding::setCollectedAction(const eTileActionType a) {
    mCollectedAction = a;
}
