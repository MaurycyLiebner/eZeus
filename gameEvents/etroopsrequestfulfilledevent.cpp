#include "etroopsrequestfulfilledevent.h"

#include "elanguage.h"
#include "estringhelpers.h"
#include "engine/eeventdata.h"
#include "engine/egameboard.h"
#include "etroopsrequestevent.h"

eTroopsRequestFulfilledEvent::eTroopsRequestFulfilledEvent(
        const eGameEventBranch branch, eGameBoard* const board) :
    ePlayerConquestEventBase(eGameEventType::troopsRequestFulfilled,
                             branch, board) {}

void eTroopsRequestFulfilledEvent::initialize(
        const eEnlistedForces& forces,
        const stdsptr<eWorldCity>& city,
        const stdsptr<eWorldCity>& rivalCity) {
    mForces = forces;
    mCity = city;
    mRivalCity = rivalCity;
}

void eTroopsRequestFulfilledEvent::trigger() {
    removeArmyEvent();
    removeConquestEvent();
    if(!mCity) return;

    const int enemyStr = mRivalCity->strength();
    const int str = mCity->strength() + mForces.strength();

    const double killFrac = std::clamp(0.5*enemyStr/str, 0., 1.);
    mForces.kill(killFrac);

    if(str > 0.75*enemyStr) {
        const int oA = mCity->army();
        const int nA = std::clamp(oA - 1, 1, 5);
        mCity->setArmy(nA);
    }

    const bool defended = str > enemyStr;

    const auto me = mainEvent<eTroopsRequestEvent>();
    if(defended) {
        me->won();
    } else {
        me->lost();
    }

    planArmyReturn();
}

std::string eTroopsRequestFulfilledEvent::longName() const {
    auto tmpl = eLanguage::text("troops_request_long_name");
    const auto none = eLanguage::text("none");
    const auto ctstr = mCity ? mCity->name() : none;
    eStringHelpers::replace(tmpl, "%1", ctstr);
    return tmpl;
}

stdsptr<eGameEvent> eTroopsRequestFulfilledEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eTroopsRequestFulfilledEvent>(
                       branch(), gameBoard());
    c->setGameBoard(gameBoard());
    c->setWorldBoard(worldBoard());
    c->mForces = mForces;
    c->mCity = mCity;
    c->mRivalCity = mRivalCity;
    c->setReason(reason);
    return c;
}
