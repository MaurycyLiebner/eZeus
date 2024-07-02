#include "eplayerconquestevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"

ePlayerConquestEvent::ePlayerConquestEvent(const eGameEventBranch branch,
                                           eGameBoard* const board) :
    ePlayerConquestEventBase(eGameEventType::playerConquestEvent,
                             branch, board) {}

void ePlayerConquestEvent::initialize(
        const eEnlistedForces& forces,
        const stdsptr<eWorldCity>& city) {
    mForces = forces;
    mCity = city;
}

void ePlayerConquestEvent::trigger() {
    const auto board = gameBoard();
    if(!board) return;
    removeArmyEvent();
    removeConquestEvent();
    if(!mCity) return;

    const int enemyStr = mCity->troops();
    const int str = mForces.strength();

    const double killFrac = std::clamp(0.5*enemyStr/str, 0., 1.);
    mForces.kill(killFrac);

    {
        const double killFrac = std::clamp(0.5*str/enemyStr, 0., 1.);
        const int t = mCity->troops();
        mCity->setTroops((1 - killFrac)*t);
    }

    const bool conquered = str > enemyStr;

    eEventData ed;
    ed.fCity = mCity;
    const auto rel = mCity->relationship();
    if(rel == eForeignCityRelationship::ally) {
        const auto w = worldBoard();
        if(w) w->attackedAlly();
        board->event(eEvent::allyAttackedByPlayer, ed);
    }
    if(conquered) {
        mCity->setConqueredBy(nullptr);
    }
    if(mCity->isColony()) {
        if(conquered) {
            board->event(eEvent::colonyRestored, ed);
            mCity->incAttitude(50);
        } else {
            board->event(eEvent::cityConquerFailed, ed);
        }
    } else {
        if(conquered) {
            board->event(eEvent::cityConquered, ed);
            board->allow(eBuildingType::commemorative, 4);
            mCity->setRelationship(eForeignCityRelationship::vassal);
        } else {
            board->event(eEvent::cityConquerFailed, ed);
        }
        mCity->incAttitude(-50);
    }

    planArmyReturn();
}

std::string ePlayerConquestEvent::longName() const {
    return eLanguage::text("player_conquest_event_long_name");
}
