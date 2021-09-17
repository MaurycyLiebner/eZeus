#include "emasonryshop.h"

#include "characters/emarbleminer.h"
#include "textures/egametextures.h"

#include "textures/emarbletile.h"

eMasonryShop::eMasonryShop(eGameBoard& board) :
    eResourceCollectBuilding(board,
                             &eBuildingTextures::fMasonryShop,
                             0, 0, nullptr,
                             [this]() { return e::make_shared<eMarbleMiner>(getBoard()); },
                             eBuildingType::masonryShop,
                             [](eTileBase* const t) {
                                if(!t->resource()) return false;
                                return t->terrain() == eTerrain::marble;
                             },
                             [](eTile* const t) {
                                if(eMarbleTile::isEdge(t)) {
                                    t->setMarbleLevel(1);
                                } else {
                                    const int l = t->marbleLevel();
                                    if(l == 0) {
                                        t->setMarbleLevel(1);
                                        t->setResource(100);
                                    } else {
                                        t->setMarbleLevel(2);
                                    }
                                }
                             }, 2, 2, 15,
                             eResourceType::marble) {

}
