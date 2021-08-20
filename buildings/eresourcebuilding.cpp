#include "eresourcebuilding.h"

#include "textures/egametextures.h"
#include "textures/ebuildingtextures.h"

eBuildingType resourceTypeToBuildingType(const eResourceBuildingType r) {
    switch(r) {
    case eResourceBuildingType::oliveTree:
        return eBuildingType::oliveTree;
    case eResourceBuildingType::vine:
        return eBuildingType::vine;
    case eResourceBuildingType::wheat:
        return eBuildingType::wheat;
    case eResourceBuildingType::carrots:
        return eBuildingType::carrots;
    case eResourceBuildingType::onions:
        return eBuildingType::onions;
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
    case eResourceBuildingType::wheat:
        return colls.fWheat.getTexture(mRipe);
    case eResourceBuildingType::carrots:
        return colls.fCarrots.getTexture(mRipe);
    case eResourceBuildingType::onions:
        return colls.fOnions.getTexture(mRipe);
    }
    return eTexture();
}

void eResourceBuilding::takeResource(const int by) {
    mResource -= by;
    if(mResource <= 0) {
        mResource = 0;
        mRipe = 0;
    }
}

void eResourceBuilding::timeChanged() {
    if(time() >= mNextRipe) {
        mNextRipe = time() + 5000;
        if(mRipe >= 5) return;
        if(++mRipe == 5) {
            mResource = 1;
        }
    }
}
