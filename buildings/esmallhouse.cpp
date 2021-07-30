#include "esmallhouse.h"

#include <algorithm>

eSmallHouse::eSmallHouse(std::vector<eBuildingTextures>& texs) :
    eBuilding(eBuildingType::house), mTextures(texs) {

}

eTexture eSmallHouse::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& coll = mTextures[sizeId].fSmallHouses[mLevel];
    const int texId = time() % coll.size();
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
