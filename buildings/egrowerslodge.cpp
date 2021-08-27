#include "egrowerslodge.h"

#include "textures/egametextures.h"
#include "characters/actions/ecarttransporteraction.h"
#include "characters/actions/egroweraction.h"

eGrowersLodge::eGrowersLodge(eGameBoard& board) :
    eBuildingWithResource(board, eBuildingType::growersLodge, 2, 2, 12),
    mTextures(eGameTextures::buildings()) {

}

eTexture eGrowersLodge::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fGrowersLodge;
}

std::vector<eOverlay> eGrowersLodge::
    getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto texs = mTextures[sizeId];
    const auto& coll = texs.fGrowersLodgeOverlay;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = -1.45;
    o.fY = -2.2;
    std::vector<eOverlay> os;
    os.push_back(o);
    if(mGrapes > 0) {
        eOverlay grapes;
        const auto& coll = texs.fWaitingGrapes;
        const int resMax = coll.size() - 1;
        const int res = std::clamp(mGrapes - 1, 0, resMax);
        grapes.fTex = coll.getTexture(res);
        grapes.fX = -0.2;
        grapes.fY = -1.7;
        os.push_back(grapes);
    }
    if(mOlives > 0) {
        eOverlay olives;
        const auto& coll = texs.fWaitingOlives;
        const int resMax = coll.size() - 1;
        const int res = std::clamp(mOlives - 1, 0, resMax);
        olives.fTex = coll.getTexture(res);
        olives.fX = -0.5;
        olives.fY = -1.85;
        os.push_back(olives);
    }
    return os;
}

void eGrowersLodge::timeChanged() {
    if(time() > mGrowerSpawnTime) {
        if(!mGrower1) {
            spawnGrower(&eGrowersLodge::mGrower1);
        } else if(!mGrower2) {
            spawnGrower(&eGrowersLodge::mGrower2);
        }
        mGrowerSpawnTime = time() + mGrowerWaitTime;
    }
    if(!mCart && time() > mCartSpawnTime) {
        mCartSpawnTime = time() + mCartWaitTime;
        const bool r = spawnCart(eResourceType::olives);
        if(!r) spawnCart(eResourceType::grapes);
    }
    eBuildingWithResource::timeChanged();
}

int eGrowersLodge::add(const eResourceType type, const int count) {
    if(type == eResourceType::olives) {
        const int r = std::clamp(mOlives + count, 0, mMaxResource - mGrapes);
        const int result = r - mOlives;
        mOlives = r;
        return result;
    } else if(type == eResourceType::grapes) {
        const int r = std::clamp(mGrapes + count, 0, mMaxResource - mOlives);
        const int result = r - mGrapes;
        mGrapes = r;
        return result;
    }
    return 0;
}

int eGrowersLodge::take(const eResourceType type, const int count) {
    if(type == eResourceType::olives) {
        const int result = std::clamp(count, 0, mOlives);
        mOlives -= result;
        return result;
    } else if(type == eResourceType::grapes) {
        const int result = std::clamp(count, 0, mGrapes);
        mGrapes -= result;
        return result;
    }
    return 0;
}

int eGrowersLodge::count(const eResourceType type) const {
    if(type == eResourceType::olives) {
        return mOlives;
    } else if(type == eResourceType::grapes) {
        return mGrapes;
    }
    return 0;
}

int eGrowersLodge::spaceLeft(const eResourceType type) const {
    if(type == eResourceType::olives ||
       type == eResourceType::grapes) {
        return mMaxResource - mOlives - mGrapes;
    }
    return 0;
}

bool eGrowersLodge::spawnCart(const eResourceType resType) {
    if(count(resType) <= 0) return false;
    mCart = e::make_shared<eCartTransporter>(getBoard());
    const auto t = tile();
    mCart->changeTile(t);
    const eStdPointer<eGrowersLodge> tptr(this);
    const eStdPointer<eCartTransporter> hptr(mCart);
    const auto foundAct = [tptr, this, hptr, resType] {
        if(!tptr || !hptr) return;
        const int took = take(resType, 8);
        hptr->setResource(resType, took);
    };
    const auto finishAct = [tptr, this, hptr]() {
        if(hptr) {
            hptr->changeTile(nullptr);
        }
        if(tptr) {
            mCart.reset();
            mCartSpawnTime = time() + mCartWaitTime;
        }
    };
    const auto failAct = [tptr, this, hptr, finishAct]() {
        if(!tptr || !hptr) return;
        add(hptr->resourceType(), hptr->resourceCount());
        finishAct();
    };
    const auto a = e::make_shared<eCartTransporterAction>(
                       tileRect(), mCart.get(),
                       eCartActionType::give, resType,
                       foundAct, failAct, finishAct);
    mCart->setAction(a);
    return true;
}

bool eGrowersLodge::spawnGrower(const eGrowerPtr grower) {
    if(mGrapes + mOlives >= mMaxResource) return false;
    const auto t = tile();
    auto& g = this->*grower;
    this->*grower = e::make_shared<eGrower>(getBoard());
    g->changeTile(t);
    const eStdPointer<eGrowersLodge> tptr(this);
    const auto finishAct = [tptr, this, grower]() {
        if(!tptr) return;
        auto& g = this->*grower;
        if(g) {
            add(eResourceType::olives, g->olives());
            add(eResourceType::grapes, g->grapes());
            g->changeTile(nullptr);
            g.reset();
        }
        mGrowerSpawnTime = time() + mGrowerWaitTime;
    };
    const auto a = e::make_shared<eGrowerAction>(
                       tileRect(), g.get(),
                       finishAct, finishAct);
    g->setAction(a);
    return true;
}
