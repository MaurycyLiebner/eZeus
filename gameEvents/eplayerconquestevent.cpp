#include "eplayerconquestevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"

ePlayerConquestEvent::ePlayerConquestEvent(
        const eGameEventBranch branch,
        eGameBoard& board) :
    ePlayerConquestEventBase(eGameEventType::playerConquestEvent,
                             branch, board) {}

void ePlayerConquestEvent::initialize(
        const eEnlistedForces& forces,
        const stdsptr<eWorldCity>& city) {
    mForces = forces;
    mCity = city;
}

void ePlayerConquestEvent::trigger() {
    removeArmyEvent();
    removeConquestEvent();
    if(!mCity) return;
    auto& board = getBoard();

    const int enemyStr = mCity->strength();
    const int str = mForces.strength();

    const double killFrac = std::clamp(0.5*enemyStr/str, 0., 1.);
    mForces.kill(killFrac);

    if(str > 0.75*enemyStr) {
        const int oA = mCity->army();
        const int nA = std::clamp(oA - 1, 1, 5);
        mCity->setArmy(nA);
    }

    const bool conquered = str > enemyStr;

    eEventData ed;
    ed.fCity = mCity;
    const auto rel = mCity->relationship();
    if(rel == eForeignCityRelationship::ally) {
        auto& worldBoard = board.getWorldBoard();
        worldBoard.attackedAlly();
        board.event(eEvent::allyAttackedByPlayer, ed);
    }
    if(conquered) {
        board.event(eEvent::cityConquered, ed);
        board.allow(eBuildingType::commemorative, 4);
        mCity->setRelationship(eForeignCityRelationship::vassal);
    } else {
        board.event(eEvent::cityConquerFailed, ed);
    }
    mCity->incAttitude(-50);

    planArmyReturn();
}

std::string ePlayerConquestEvent::longName() const {
    return eLanguage::text("player_conquest_event_long_name");
}

stdsptr<eGameEvent> ePlayerConquestEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<ePlayerConquestEvent>(branch(), getBoard());
    c->mForces = mForces;
    c->mCity = mCity;
    c->setReason(reason);
    return c;
}
