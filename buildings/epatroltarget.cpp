#include "epatroltarget.h"

#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"
#include "characters/actions/emovepathaction.h"
#include "engine/epathfinder.h"
#include "epathfindtask.h"
#include "engine/ethreadpool.h"
#include "characters/actions/ewaitaction.h"
#include "characters/echaracter.h"
#include "engine/egameboard.h"

ePatrolTarget::ePatrolTarget(eGameBoard& board,
                             const eBaseTex baseTex,
                             const double overlayX,
                             const double overlayY,
                             const eOverlays overlays,
                             const eCharGenerator& charGen,
                             const eBuildingType type,
                             const int sw, const int sh,
                             const int maxEmployees) :
    ePatrolBuilding(board, baseTex,
                    overlayX, overlayY,
                    overlays, charGen,
                    type, sw, sh,
                    maxEmployees),
    mCharGen(charGen) {}

void ePatrolTarget::arrived() {
    mAvailable = mAvailableWaitTime;
    setSpawnPatrolers(true);
}

void ePatrolTarget::timeChanged(const int by) {
    mAvailable -= by;
    if(mAvailable < 0) setSpawnPatrolers(false);
    ePatrolBuilding::timeChanged(by);
}

void ePatrolTarget::read(eReadStream& src) {
    ePatrolBuilding::read(src);
    src >> mAvailable;
}

void ePatrolTarget::write(eWriteStream& dst) const {
    ePatrolBuilding::write(dst);
    dst << mAvailable;
}
