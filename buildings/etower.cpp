#include "etower.h"

#include "textures/egametextures.h"

#include "characters/actions/earcheraction.h"

eTower::eTower(eGameBoard& board) :
    eEmployingBuilding(board, eBuildingType::tower, 2, 2, 15) {}

std::shared_ptr<eTexture>
eTower::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings();
    return texs[sizeId].fTower;
}

std::vector<eOverlay>
eTower::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::characters();
    const auto& colls = texs[sizeId].fArcher.fPatrol;
    const int tt = textureTime();
    const int idid = tt/50 % 8;
    const int ids[8] = {5, 0, 3, 7, 4, 2, 6, 1};
    const int id = ids[idid];
    const auto& coll = colls[id];
    eOverlay o;
    o.fTex = coll.getTexture(tt % coll.size());
    o.fX = -3.5;
    o.fY = -5.5;
    return {o};
}

void eTower::timeChanged(const int by) {
    const int t = time();
    if(mSpawnPatrolers && enabled()) {
        if(!mArcher && t >= mSpawnTime) {
            spawn();
            mSpawnTime = t + mWaitTime;
        }
    }
    eEmployingBuilding::timeChanged(by);
}

bool eTower::spawn() {
    mArcher = e::make_shared<eArcher>(getBoard());
    mArcher->changeTile(centerTile());
    const eStdPointer<eTower> tptr(this);
    const eStdPointer<eArcher> cptr(mArcher);
    const auto finishAct = [tptr, this, cptr]() {
        if(cptr) cptr->changeTile(nullptr);
        if(tptr) {
            mSpawnTime = time() + mWaitTime;
            mArcher.reset();
        }
    };
    const auto a = e::make_shared<eArcherAction>(
                       mArcher.get(), finishAct, finishAct);
    mArcher->setAction(a);
    return true;
}

