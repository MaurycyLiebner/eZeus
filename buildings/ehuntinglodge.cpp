#include "ehuntinglodge.h"

#include "characters/ehunter.h"
#include "textures/egametextures.h"

#include "characters/ehunter.h"
#include "characters/eboar.h"
#include "characters/actions/ehuntaction.h"

#include "characters/actions/ecollectresourceaction.h"

eHuntingLodge::eHuntingLodge(eGameBoard& board) :
    eResourceBuildingBase(board, eBuildingType::huntingLodge, 2, 2),
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
    if(!mSpawned && time() > mSpawnTime) {
        mSpawned = spawn();
        mSpawnTime = time() + mWaitTime;
    }
}

bool eHuntingLodge::spawn() {
    if(resource() >= maxResource()) return false;
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

    const auto h = new eHunter(getBoard());
    h->setTile(t);
    const auto finishAct = [this, h]() {
        incResource(h->collected());
        const auto t = h->tile();
        t->removeCharacter(h);
        mSpawned = false;
        mSpawnTime = time() + mWaitTime;
        delete h;
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
    const auto a = new eHuntAction(h, hasRes, hasCollRes,
                                   finishAct, finishAct);
    h->setAction(a);
    t->addCharacter(h);
    return true;
}
