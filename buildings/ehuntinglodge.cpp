#include "ehuntinglodge.h"

#include "characters/ehunter.h"
#include "textures/egametextures.h"

#include "characters/ehunter.h"
#include "characters/eboar.h"
#include "characters/actions/ehuntaction.h"

#include "characters/actions/ecollectresourceaction.h"

eHuntingLodge::eHuntingLodge(eGameBoard& board) :
    eResourceBuildingBase(board, eBuildingType::huntingLodge, 2, 2,
                          eResourceType::meat),
    mTextures(eGameTextures::buildings())  {

}

eTexture eHuntingLodge::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fHuntingLodge;
}

std::vector<eOverlay> eHuntingLodge::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto texs = mTextures[sizeId];
    const auto& coll = texs.fHuntingLodgeOverlay;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = -1.95;
    o.fY = -2.4;
    if(resource() > 0) {
        eOverlay meat;
        const int res = std::clamp(resource() - 1, 0, 4);
        meat.fTex = texs.fWaitingMeat.getTexture(res);
        meat.fX = -0.5;
        meat.fY = -2;

        return std::vector<eOverlay>({o, meat});
    }
    return std::vector<eOverlay>({o});
}

void eHuntingLodge::timeChanged() {
    eResourceBuildingBase::timeChanged();
    if(!mSpawned && time() > mSpawnTime) {
        mSpawned = spawn();
        mSpawnTime = time() + mWaitTime;
    }
}

bool eHuntingLodge::spawn() {
    if(resource() >= maxResource()) return false;
    const auto t = tile();
    const auto h = e::make_shared<eHunter>(getBoard());
    h->changeTile(t);
    const eStdPointer<eHuntingLodge> tptr(this);
    const eStdPointer<eHunter> hptr(h);
    const auto finishAct = [tptr, this, hptr]() {
        const auto h = &*hptr;
        if(tptr) {
            if(h) add(eResourceType::meat, h->collected());
            mSpawned = false;
            mSpawnTime = time() + mWaitTime;
        }
        if(h) h->changeTile(nullptr);
    };
    const auto a = e::make_shared<eHuntAction>(
                       tileRect(), h.get(), finishAct, finishAct);
    h->setAction(a);
    return true;
}
