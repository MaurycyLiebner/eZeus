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

    const auto tt = t->top<eTile>();
    const auto b = t->bottom<eTile>();
    const auto l = t->left<eTile>();
    const auto r = t->right<eTile>();

    const auto ttt = tt ? tt->underBuildingType() : eBuildingType::none;
    const auto bt = b ? b->underBuildingType() : eBuildingType::none;
    const auto lt = l ? l->underBuildingType() : eBuildingType::none;
    const auto rt = r ? r->underBuildingType() : eBuildingType::none;

    const bool ttb = ttt == eBuildingType::wall ||
                     ttt == eBuildingType::tower ||
                     ttt == eBuildingType::gatehouse;
    const bool lb = lt == eBuildingType::wall ||
                    lt == eBuildingType::tower ||
                    lt == eBuildingType::gatehouse;
    const bool bb = bt == eBuildingType::wall ||
                    bt == eBuildingType::tower ||
                    bt == eBuildingType::gatehouse;
    const bool rb = rt == eBuildingType::wall ||
                    rt == eBuildingType::tower ||
                    rt == eBuildingType::gatehouse;

    int id = 0;

    if(tlb && brb && trb && blb) {
        if(bb && rb && lb) {
            id = 0;
        } else if(bb && lb) {
            id = 21;
        } else if(bb && rb) {
            id = 19;
        } else if(ttb && bb) {
            id = 17;
        } else if(rb && lb && !ttb) {
            id = 18;
        } else if(bb) {
            id = 7;
        } else {
            id = 22;
        }
    } else if(tlb && brb && trb) {
        if(tlt != eBuildingType::wall) {
            id = 32;
        } else {
            id = 1;
        }
    } else if(blb && brb && trb) {
        if(bb) {
            if(rb) {
                id = 2;
            } else {
                id = 7;
            }
        } else {
            id = 34;
        }
    } else if(blb && brb && tlb) {
        if(bb) {
            if(rb && !lb && !ttb) {
                id = 7;
            } else if(!rb && !lb && !ttb) {
                id = 7;
            } else if(rb) {
                if(lb) {
                    id = 3;
                } else {
                    id = 2;
                }
            } else {
                id = 3;
            }
        } else {
            if(lb) {
                id = 22;
            } else {
                id = 35;
            }
        }
    } else if(blb && tlb && trb) {
        if(trt != eBuildingType::wall) {
            id = 31;
        } else {
            id = 4;
        }
    } else if(brb && blb && tlb) {
        if(bb) {
            if(rb) {
                id = 7;
            } else {
                id = 30;
            }
        } else {
            id = 8;
        }
    } else if(brb && blb && trb) {
        id = 9;
    } else if(brb && blb) {
        if(bb) {
            id = 7;
        } else {
            id = 22;
        }
    } else if(trb && tlb) {
        id = 12;
    } else if(trb && brb) {
        if(rb) {
            id = 5;
        } else {
            id = 27;
        }
    } else if(tlb && blb) {
        if(lb) {
            id = 10;
        } else {
            id = 28;
        }
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
