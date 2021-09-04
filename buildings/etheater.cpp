#include "etheater.h"

#include "characters/eactor.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"

eTheater::eTheater(eGameBoard& board) :
    ePatrolBuilding(board, &eBuildingTextures::fTheater,
                    -1.25, -6.5,
                    &eBuildingTextures::fTheaterOverlay,
                    [this]() { return e::make_shared<eActor>(getBoard()); },
                    eBuildingType::theater, 5, 5, 18)  {

}

void eTheater::timeChanged(const int by) {
    (void)by;
    const int t = time();
    if(!mChar && t >= mSpawnTime) {
        spawnGetActor();
        mSpawnTime = t + mWaitTime;
    }
}

void eTheater::spawnGetActor() {

}
