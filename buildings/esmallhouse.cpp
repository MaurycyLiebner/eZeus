#include "esmallhouse.h"

#include <algorithm>
#include "textures/egametextures.h"

eSmallHouse::eSmallHouse() :
    eBuilding(eBuildingType::house, 2, 2),
    mTextures(eGameTextures::buildings()) {

}

eTexture eSmallHouse::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& coll = mTextures[sizeId].fSmallHouses[mLevel];
    const int texId = seed() % coll.size();
    return coll.getTexture(texId);
}

void eSmallHouse::levelUp() {
    setLevel(mLevel + 1);
}

void eSmallHouse::levelDown() {
    setLevel(mLevel - 1);
}

void eSmallHouse::setLevel(const int l) {
    mLevel = std::clamp(l, 0, 7);
}
