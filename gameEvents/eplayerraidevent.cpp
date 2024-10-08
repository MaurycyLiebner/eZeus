#include "eplayerraidevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"
#include "engine/egifthelpers.h"
#include "eraidresourceevent.h"

ePlayerRaidEvent::ePlayerRaidEvent(
        const eGameEventBranch branch,
        eGameBoard* const board) :
    ePlayerConquestEventBase(eGameEventType::playerRaidEvent,
                             branch, board) {}

void ePlayerRaidEvent::initialize(
        const eEnlistedForces& forces,
        const stdsptr<eWorldCity>& city,
        const eResourceType resource) {
    mForces = forces;
    mCity = city;
    mResource = resource;
}

void ePlayerRaidEvent::trigger() {
    removeArmyEvent();
    removeConquestEvent();
    if(!mCity) return;
    const auto board = gameBoard();
    if(!board) return;

    const int enemyStr = mCity->troops();
    const int str = mForces.strength();

    const double killFrac = std::clamp(0.5*enemyStr/str, 0., 1.);
    mForces.kill(killFrac);

    const bool raided = str > 0.75*enemyStr;
    eEventData ed;
    ed.fCity = mCity;
    const auto rel = mCity->relationship();
    if(rel == eForeignCityRelationship::ally) {
        const auto wboard = worldBoard();
        wboard->attackedAlly();
        board->event(eEvent::allyAttackedByPlayer, ed);
    }
    if(raided) {
        eResourceType res = mResource;
        if(res == eResourceType::none) {
            if(eRand::rand() % 2) {
                res = eResourceType::drachmas;
            } else {
                const auto& sells = mCity->sells();
                if(sells.empty()) {
                    res = eResourceType::drachmas;
                } else {
                    const int ss = sells.size();
                    res = sells[eRand::rand() % ss].fType;
                }
            }
        }
        const int count = 2*eGiftHelpers::giftCount(res);
        const auto e = e::make_shared<eRaidResourceEvent>(
                           eGameEventBranch::child);
        const auto boardDate = board->date();
        const int period = 75;
        const auto date = boardDate + period;
        e->initializeDate(date, period, 1);
        e->initialize(true, res, count, mCity);
        addConsequence(e);
    } else {
        board->event(eEvent::cityRaidFailed, ed);
    }

    planArmyReturn();
}

std::string ePlayerRaidEvent::longName() const {
    return eLanguage::text("player_raid_event_long_name");
}

void ePlayerRaidEvent::write(eWriteStream& dst) const {
    ePlayerConquestEventBase::write(dst);
    dst << mResource;
}

void ePlayerRaidEvent::read(eReadStream& src) {
    ePlayerConquestEventBase::read(src);
    src >> mResource;
}
