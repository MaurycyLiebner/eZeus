#include "eresourcebuilding.h"

#include "textures/egametextures.h"
#include "textures/ebuildingtextures.h"

eBuildingType resourceTypeToBuildingType(const eResourceType r) {
    switch(r) {
    case eResourceType::oliveTree:
        return eBuildingType::oliveTree;
    case eResourceType::vine:
        return eBuildingType::vine;
    case eResourceType::wheat:
        return eBuildingType::wheat;
    case eResourceType::carrots:
        return eBuildingType::carrots;
    case eResourceType::onions:
        return eBuildingType::onions;
    }
    return eBuildingType::oliveTree;
}

eResourceBuilding::eResourceBuilding(
        eGameBoard& board, const eResourceType type) :
    eBuilding(board, resourceTypeToBuildingType(type), 1, 1),
    mType(type) {

}

eTexture eResourceBuilding::getTexture(const eTileSize size) const {
    const auto& texs = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    const auto& colls = texs[sizeId];
    switch(mType) {
    case eResourceType::oliveTree:
        return colls.fOliveTree.getTexture(mRipe);
    case eResourceType::vine:
        return colls.fVine.getTexture(mRipe);
    case eResourceType::wheat:
        return colls.fWheat.getTexture(mRipe);
    case eResourceType::carrots:
        return colls.fCarrots.getTexture(mRipe);
    case eResourceType::onions:
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
