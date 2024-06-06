#include "eanimalbuilding.h"

eAnimalBuilding::eAnimalBuilding(
         eGameBoard& board,
         eCharacter* const a,
         const eBuildingType type) :
    eBuilding(board, type, 1, 2),
    mA(a) {

}

eAnimalBuilding::~eAnimalBuilding() {
    if(mA) mA->kill();
}

void eAnimalBuilding::nextMonth() {
    const bool isCattle = type() == eBuildingType::cattle;
    if(!mA && !isCattle) erase();
}

void eAnimalBuilding::read(eReadStream& src) {
    eBuilding::read(src);
    auto& board = getBoard();
    src.readCharacter(&board, [this](eCharacter* const c) {
        mA = c;
    });
}

void eAnimalBuilding::write(eWriteStream& dst) const {
    eBuilding::write(dst);
    dst.writeCharacter(mA);
}

void eAnimalBuilding::setAnimal(eCharacter* const a) {
    mA = a;
}
