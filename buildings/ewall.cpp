#include "ewall.h"

#include "textures/egametextures.h"

eWall::eWall(eGameBoard& board) :
    eBuilding(board, eBuildingType::wall, 1, 1) {

}

std::shared_ptr<eTexture>
eWall::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const auto& wll = blds.fWall;
    const auto t = centerTile();

    const auto tl = t->topLeft<eTile>();
    const auto br = t->bottomRight<eTile>();
    const auto bl = t->bottomLeft<eTile>();
    const auto tr = t->topRight<eTile>();

    const auto tlt = tl ? tl->underBuildingType() : eBuildingType::none;
    const auto brt = br ? br->underBuildingType() : eBuildingType::none;
    const auto blt = bl ? bl->underBuildingType() : eBuildingType::none;
    const auto trt = tr ? tr->underBuildingType() : eBuildingType::none;

    const bool tlb = tlt == eBuildingType::wall ||
                     tlt == eBuildingType::tower ||
                     tlt == eBuildingType::gatehouse;
    const bool brb = brt == eBuildingType::wall ||
                     brt == eBuildingType::tower ||
                     brt == eBuildingType::gatehouse;
    const bool blb = blt == eBuildingType::wall ||
                     blt == eBuildingType::tower ||
                     blt == eBuildingType::gatehouse;
    const bool trb = trt == eBuildingType::wall ||
                     trt == eBuildingType::tower ||
                     trt == eBuildingType::gatehouse;

    int id = 0;

    if(tlb && brb && trb && blb) {
        id = 22;
    } else if(tlb && brb && trb) {
        id = 1;
    } else if(blb && brb && trb) {
        id = 34;
    } else if(blb && brb && tlb) {
        id = 35;
    } else if(blb && tlb && trb) {
        id = 4;
    } else if(brb && blb && tlb) {
        id = 8;
    } else if(brb && blb && trb) {
        id = 9;
    } else if(brb && blb) {
        id = 22;
    } else if(trb && tlb) {
        id = 12;
    } else if(trb && brb) {
        id = 27;
    } else if(tlb && blb) {
        id = 28;
    } else if(tlb && brb) {
        id = 32;
    } else if(trb && blb) {
        id = 31;
    } else if(brb) {
        id = 5;
    } else if(blb) {
        id = 10;
    } else if(tlb) {
        id = 15;
    } else if(trb) {
        id = 16;
    } else {
        id = 26;
    }

    return wll.getTexture(id);
}
