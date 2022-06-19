#include "egrowerslodge.h"

#include "textures/egametextures.h"
#include "characters/actions/ecarttransporteraction.h"
#include "characters/actions/egroweraction.h"

eGrowersLodge::eGrowersLodge(eGameBoard& board, const eGrowerType type) :
    eEmployingBuilding(board,
                       type == eGrowerType::grapesAndOlives ?
                           eBuildingType::growersLodge :
                           eBuildingType::orangeTendersLodge, 2, 2, 12),
    mTextures(eGameTextures::buildings()),
    mType(type) {

}

eGrowersLodge::~eGrowersLodge() {
    if(mCart) mCart->kill();
    if(mGrower1) mGrower1->kill();
    if(mGrower2) mGrower2->kill();
}

std::shared_ptr<eTexture> eGrowersLodge::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = mTextures[sizeId];
    switch(mType) {
    case eGrowerType::grapesAndOlives:
        return texs.fGrowersLodge;
    case eGrowerType::oranges:
        return texs.fOrangeTendersLodge;
    }
    return nullptr;
}

std::vector<eOverlay> eGrowersLodge::
    getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = mTextures[sizeId];
    std::vector<eOverlay> os;

    switch(mType) {
    case eGrowerType::grapesAndOlives: {
        const auto& coll = texs.fGrowersLodgeOverlay;
        const int texId = textureTime() % coll.size();
        eOverlay o;
        o.fTex = coll.getTexture(texId);
        o.fX = -1.45;
        o.fY = -2.2;
        os.push_back(o);
    } break;
    case eGrowerType::oranges: {
        const auto& coll = texs.fOrangeTendersLodgeOverlay;
        const int texId = textureTime() % coll.size();
        eOverlay o;
        o.fTex = coll.getTexture(texId);
        o.fX = -1.75;
        o.fY = -2.3;
        os.push_back(o);
    } break;
    }

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
    if(mOranges > 0) {
        eOverlay oranges;
        const auto& coll = texs.fWaitingOranges;
        const int resMax = coll.size() - 1;
        const int res = std::clamp(mOranges - 1, 0, resMax);
        oranges.fTex = coll.getTexture(res);
        oranges.fX = 0.00;
        oranges.fY = -1.80;
        os.push_back(oranges);
    }
    return os;
}

void eGrowersLodge::timeChanged(const int by) {
    if(enabled()) {
        const bool hasRes = mGrapes > 0 || mOlives > 0 || mOranges > 0;
        if(!mCart) {
            spawnCart(mCart, eCartActionTypeSupport::give);
        } else if(mCart && mCart->waiting() && hasRes) {
            if(mGrapes > 0) {
                const int a = mCart->add(eResourceType::grapes, mGrapes);
                mGrapes -= a;
            } else if(mOlives > 0) {
                const int a = mCart->add(eResourceType::olives, mOlives);
                mOlives -= a;
            } else if(mOranges > 0) {
                const int a = mCart->add(eResourceType::oranges, mOranges);
                mOranges -= a;
            }
        }
        if(mSpawnEnabled) {
            mSpawnTime1 += by;
            if(!mGrower1 && mSpawnTime1 > mWaitTime) {
                mSpawnTime1 -= mWaitTime;
                spawnGrower(&eGrowersLodge::mGrower1,
                            &eGrowersLodge::mSpawnTime1);
            }
            mSpawnTime2 += by;
            if(!mGrower2 && mSpawnTime2 > mWaitTime) {
                mSpawnTime2 -= mWaitTime;
                spawnGrower(&eGrowersLodge::mGrower2,
                            &eGrowersLodge::mSpawnTime2);
            }
        }
    }
    eEmployingBuilding::timeChanged(by);
}

int eGrowersLodge::add(const eResourceType type, const int count) {
    const int sl = mMaxResource - mGrapes - mOlives - mOranges;
    const int r = std::clamp(count, 0, sl);
    if(type == eResourceType::olives) {
        mOlives += r;
    } else if(type == eResourceType::grapes) {
        mGrapes += r;
    } else if(type == eResourceType::oranges) {
        mOranges += r;
    } else {
        return 0;
    }
    return r;
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
    } else if(type == eResourceType::oranges) {
        const int result = std::clamp(count, 0, mOranges);
        mOranges -= result;
        return result;
    }
    return 0;
}

int eGrowersLodge::count(const eResourceType type) const {
    if(type == eResourceType::olives) {
        return mOlives;
    } else if(type == eResourceType::grapes) {
        return mGrapes;
    } else if(type == eResourceType::oranges) {
        return mOranges;
    }
    return 0;
}

int eGrowersLodge::spaceLeft(const eResourceType type) const {
    switch(mType) {
    case eGrowerType::grapesAndOlives:
        if(type == eResourceType::olives ||
           type == eResourceType::grapes) {
            return mMaxResource - mOlives - mGrapes;
        }
        break;
    case eGrowerType::oranges:
        if(type == eResourceType::oranges) {
            return mMaxResource - mOranges;
        }
        break;
    }
    return 0;
}

std::vector<eCartTask> eGrowersLodge::cartTasks() const {
    std::vector<eCartTask> tasks;

    if(mGrapes > 0) {
        eCartTask task;
        task.fType = eCartActionType::give;
        task.fResource = eResourceType::grapes;
        task.fMaxCount = mGrapes;
        tasks.push_back(task);
    }

    if(mOlives > 0) {
        eCartTask task;
        task.fType = eCartActionType::give;
        task.fResource = eResourceType::olives;
        task.fMaxCount = mOlives;
        tasks.push_back(task);
    }

    if(mOranges > 0) {
        eCartTask task;
        task.fType = eCartActionType::give;
        task.fResource = eResourceType::oranges;
        task.fMaxCount = mOranges;
        tasks.push_back(task);
    }

    return tasks;
}

bool eGrowersLodge::spawnGrower(const eGrowerPtr grower,
                                const eTimePtr time) {
    const auto t = centerTile();
    auto& g = this->*grower;
    this->*grower = e::make_shared<eGrower>(getBoard(), mType);
    g->changeTile(t);
    const eStdPointer<eGrowersLodge> tptr(this);
    const auto finishAct = [tptr, this, grower, time]() {
        if(!tptr) return;
        auto& g = this->*grower;
        if(g) g->kill();
        g = nullptr;
        this->*time = 0;
    };
    const auto a = e::make_shared<eGrowerAction>(
                       mType, this, g.get(),
                       finishAct, finishAct);
    g->setAction(a);
    return true;
}
