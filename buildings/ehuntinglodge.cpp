#include "ehuntinglodge.h"

#include "characters/ehunter.h"
#include "textures/egametextures.h"

#include "characters/ehunter.h"
#include "characters/eboar.h"
#include "characters/actions/ehuntaction.h"

#include "characters/actions/ecollectresourceaction.h"

eHuntingLodge::eHuntingLodge(eGameBoard& board) :
    eBuilding(board, eBuildingType::huntingLodge, 2, 2),
    mTextures(eGameTextures::buildings())  {

}

eTexture eHuntingLodge::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fHuntingLodge;
}

std::vector<eOverlay> eHuntingLodge::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& coll = mTextures[sizeId].fHuntingLodgeOverlay;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = -1.95;
    o.fY = -2.4;
    return std::vector<eOverlay>({o});
}

void eHuntingLodge::timeChanged() {
    if(time() > mSpawnTime) {
        const bool r = spawn();
        if(r) mSpawnTime = time() + 5*mWaitTime;
        mSpawnTime = time() + mWaitTime;
    }
}

bool eHuntingLodge::spawn() {
    auto dirs = gExtractDirections(eMoveDirection::allDirections);
    if(dirs.empty()) return false;
    std::random_shuffle(dirs.begin(), dirs.end());
    eTile* t = nullptr;
    for(const auto dir : dirs) {
        t = tileNeighbour(dir, [](eTile* const tile) {
            return tile->walkable();
        });
        if(t) break;
    }
    if(!t) return false;

    const auto d = new eHunter(getBoard());
    d->setTile(t);
    const auto finishAct = [this, d]() {
        mResource += d->collected();
        const auto t = d->tile();
        t->removeCharacter(d);
        mSpawnTime = time() + mWaitTime;
        delete d;
    };
    const auto hasRes = [](eTileBase* const tile) {
        return tile->hasCharacter([](const eCharacterBase& c) {
            return c.type() == eCharacterType::boar && !c.fighting();
        });
    };
    const auto hasCollRes = [](eTile* const tile) {
        const auto cs = tile->characters();
        for(const auto c : cs) {
            if(const auto b = dynamic_cast<eBoar*>(c)) {
                if(b->dead()) return true;
            }
        }
        return false;
    };
    const auto a = new eHuntAction(d, hasRes, hasCollRes, finishAct, finishAct);
    d->setAction(a);
    t->addCharacter(d);
    return true;
}
