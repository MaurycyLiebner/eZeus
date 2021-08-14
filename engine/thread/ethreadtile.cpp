#include "ethreadtile.h"

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
        mCharacters.emplace_back().load(ch);
    }

    mUnderBuilding.load(src->underBuilding());
}

void eThreadTile::load(const eThreadTile& src) {
    setSeed(src.seed());
    setX(src.x());
    setY(src.y());
    setWalkableElev(src.walkableElev());
    setBusy(src.busy());
    setResource(src.resource());
    setTerrain(src.terrain());
    setScrub(src.scrub());
    setAltitude(src.altitude());

    mCharacters = src.mCharacters;
    mUnderBuilding = src.mUnderBuilding;
}
