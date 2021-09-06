#include "eaestheticsbuilding.h"

#include "textures/egametextures.h"

eAestheticsBuilding::eAestheticsBuilding(
        eGameBoard& board,
        const eBaseTex baseTex,
        const eBuildingType type,
        const int sw, const int sh) :
    eBuilding(board, type, sw, sh),
    mTexture(baseTex) {
    setEnabled(true);
}

std::shared_ptr<eTexture> eAestheticsBuilding::getTexture(
        const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings();
    return texs[sizeId].*mTexture;
}

eBench::eBench(eGameBoard& board) :
    eAestheticsBuilding(board, &eBuildingTextures::fBench,
                        eBuildingType::bench, 1, 1){

}

eFlowerGarden::eFlowerGarden(eGameBoard& board) :
    eAestheticsBuilding(board, &eBuildingTextures::fFlowerGarden,
                        eBuildingType::flowerGarden, 2, 2){

}

eGazebo::eGazebo(eGameBoard& board) :
    eAestheticsBuilding(board, &eBuildingTextures::fGazebo,
                        eBuildingType::gazebo, 2, 2){

}

eHedgeMaze::eHedgeMaze(eGameBoard& board) :
    eAestheticsBuilding(board, &eBuildingTextures::fHedgeMaze,
                        eBuildingType::hedgeMaze, 3, 3){

}

eFishPond::eFishPond(eGameBoard& board) :
    eAestheticsBuilding(board, &eBuildingTextures::fFishPond,
                        eBuildingType::fishPond, 4, 4){

}
