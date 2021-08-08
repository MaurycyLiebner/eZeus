#include "efountain.h"

#include "characters/ewaterdistributor.h"

eFountain::eFountain(eGameBoard& board) :
    ePatrolBuilding(board,
                    &eBuildingTextures::fFountain,
                    -1.15, -2.37,
                    &eBuildingTextures::fFountainOverlay,
                    [this]() { return new eWaterDistributor(getBoard()); },
                    eBuildingType::fountain, 2, 2)  {

}
