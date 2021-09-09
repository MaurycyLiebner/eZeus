#include "eanimalbuilding.h"

eAnimalBuilding::eAnimalBuilding(
         eGameBoard& board,
         eDomesticatedAnimal* const a,
         const eBuildingType type) :
    eBuilding(board, type, 1, 2),
    mA(a) {

}

eAnimalBuilding::~eAnimalBuilding() {
    if(mA) {
        mA->changeTile(nullptr);
    }
}

void eAnimalBuilding::nextMonth() {
    if(!mA) erase();
}
