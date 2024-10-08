#include "ewatchpost.h"

#include "characters/ewatchman.h"
#include "textures/egametextures.h"

eWatchpost::eWatchpost(eGameBoard& board) :
    ePatrolBuilding(board, &eBuildingTextures::fWatchPost,
                    -0.25, -2.1,
                    &eBuildingTextures::fWatchPostOverlay,
                    [this]() { return e::make_shared<eWatchman>(getBoard()); },
                    eBuildingType::watchPost, 2, 2, 6)  {
    eGameTextures::loadWatchpost();
}
