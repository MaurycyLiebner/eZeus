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
    if(const auto b = src->underBuilding()) {
        if(b->type() == eBuildingType::commonHouse) {
            const auto h = static_cast<eSmallHouse*>(b);
            mData1 = h->vacancies();
        }
    }

    mCharacters.clear();
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
    setOnFire(src.onFire());
    mData1 = src.mData1;

    mCharacters = src.mCharacters;
    mUnderBuilding = src.mUnderBuilding;
}

bool eThreadTile::walkable() const {
    const auto terr = terrain() & eTerrain::walkable;
    if(!static_cast<bool>(terr)) return false;
    if(isUnderBuilding() && !hasRoad()) return false;
    return true;
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
