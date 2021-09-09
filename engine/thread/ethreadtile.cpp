#include "ethreadtile.h"

#include "characters/echaracter.h"
#include "buildings/esmallhouse.h"

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
    setOnFire(src->onFire());

    mCharacters.clear();
    const auto& chars = src->characters();
    for(const auto& ch : chars) {
        mCharacters.emplace_back().load(ch.get());
    }
    mMainBuildingTile = src->building();
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
    setOnFire(src.onFire());

    mCharacters = src.mCharacters;
    mUnderBuilding = src.mUnderBuilding;
}

bool eThreadTile::hasRoad() const {
    return mUnderBuilding.type() == eBuildingType::road;
}

bool eThreadTile::hasCharacter(const eHasChar& func) const {
    for(const auto& c : mCharacters) {
        if(func(c)) return true;
    }
    return false;
}

eBuildingType eThreadTile::underBuildingType() const {
    return mUnderBuilding.type();
}

bool eThreadTile::isUnderBuilding() const {
    return mUnderBuilding.type() != eBuildingType::none;
}

int eThreadTile::houseVacancies() const {
    return mUnderBuilding.houseVacancies();
}
