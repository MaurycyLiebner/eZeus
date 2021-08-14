#include "ethreadtile.h"

eThreadTile::eThreadTile() {
}

void eThreadTile::load(eTile* const src) {
    setSeed(src->seed());
    setX(src->x());
    setY(src->y());
    setWalkableElev(src->walkableElev());
    setBusy(src->busy());
    setResource(src->resource());
    setTerrain(src->terrain());
    setScrub(src->scrub());
    setAltitude(src->altitude());

    const auto& chars = src->characters();
    for(const auto& ch : chars) {
        mCharacters.emplace_back(ch);
    }

    mUnderBuilding.load(src->underBuilding());
}
