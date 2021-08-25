#include "eresourcebuilding.h"

#include "textures/egametextures.h"
#include "textures/ebuildingtextures.h"

eBuildingType resourceTypeToBuildingType(const eResourceBuildingType r) {
    switch(r) {
    case eResourceBuildingType::oliveTree:
        return eBuildingType::oliveTree;
    case eResourceBuildingType::vine:
        return eBuildingType::vine;
    }
    return eBuildingType::oliveTree;
}

eResourceBuilding::eResourceBuilding(
        eGameBoard& board, const eResourceBuildingType type) :
    eBuilding(board, resourceTypeToBuildingType(type), 1, 1),
    mType(type) {

}

eTexture eResourceBuilding::getTexture(const eTileSize size) const {
    const auto& texs = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    const auto& colls = texs[sizeId];
    switch(mType) {
    case eResourceBuildingType::oliveTree:
        return colls.fOliveTree.getTexture(mRipe);
    case eResourceBuildingType::vine:
        return colls.fVine.getTexture(mRipe);
    }
    return eTexture();
}

int eResourceBuilding::takeResource(const int by) {
    const int take = std::clamp(by, 0, mResource);
    mResource -= by;
    if(mResource == 0) mRipe = 0;
    return take;
}

void eResourceBuilding::timeChanged() {
    if(time() >= mNextRipe) {
        mNextRipe = time() + 2500;
        if(mRipe >= 5) return;
        if(++mRipe == 5) {
            mResource = 1;
        }
    }
}
