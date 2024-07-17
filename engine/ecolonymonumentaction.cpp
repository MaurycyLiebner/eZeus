#include "ecolonymonumentaction.h"

#include "engine/eworldcity.h"
#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"

eColonyMonumentAction::eColonyMonumentAction(
        const stdsptr<eWorldCity>& city) :
    ePlannedAction(false, 1000, ePlannedActionType::colonyMonument),
    mCity(city) {}

eColonyMonumentAction::eColonyMonumentAction() :
    eColonyMonumentAction(nullptr) {}

void eColonyMonumentAction::trigger(eGameBoard& board) {
    eEventData ed;
    ed.fCity = mCity;
    board.event(eEvent::colonyMonument, ed);
    board.allow(eBuildingType::commemorative, 2);
}

void eColonyMonumentAction::read(eReadStream& src, eGameBoard& board) {
    ePlannedAction::read(src, board);
    src.readCity(&board, [this](const stdsptr<eWorldCity>& city) {
        mCity = city;
    });
}

void eColonyMonumentAction::write(eWriteStream& dst) const {
    ePlannedAction::write(dst);
    dst.writeCity(mCity.get());
}
