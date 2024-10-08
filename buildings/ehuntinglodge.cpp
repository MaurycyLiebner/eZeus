#include "ehuntinglodge.h"

#include "characters/ehunter.h"
#include "textures/egametextures.h"
#include "characters/actions/ehuntaction.h"
#include "enumbers.h"

#include <algorithm>

eHuntingLodge::eHuntingLodge(eGameBoard& board) :
    eResourceCollectBuildingBase(board, eBuildingType::huntingLodge,
                          2, 2, 8, eResourceType::meat) {
    eGameTextures::loadHuntingLodge();
}

eHuntingLodge::~eHuntingLodge() {
    if(mHunter) mHunter->kill();
}

std::shared_ptr<eTexture> eHuntingLodge::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return eGameTextures::buildings()[sizeId].fHuntingLodge;
}

std::vector<eOverlay> eHuntingLodge::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];
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

void eHuntingLodge::timeChanged(const int by) {
    eResourceCollectBuildingBase::timeChanged(by);
    if(!mHunter) {
        mSpawnTime += by;
        const double eff = effectiveness();
        const int wait = eNumbers::sHuntingLodgeWaitPeriod/eff;
        if(mSpawnTime > wait) {
            mSpawnTime -= wait;
            spawn();
        }
    }
}

void eHuntingLodge::read(eReadStream& src) {
    eResourceCollectBuildingBase::read(src);
    src >> mSpawnTime;
    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mHunter = static_cast<eHunter*>(c);
    });
}

void eHuntingLodge::write(eWriteStream& dst) const {
    eResourceCollectBuildingBase::write(dst);
    dst << mSpawnTime;
    dst.writeCharacter(mHunter);
}

bool eHuntingLodge::spawn() {
    const auto t = centerTile();
    const auto h = e::make_shared<eHunter>(getBoard());
    mHunter = h.get();
    h->changeTile(t);
    const auto a = e::make_shared<eHuntAction>(this, h.get());
    h->setAction(a);
    return true;
}
