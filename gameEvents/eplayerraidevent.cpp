#include "eplayerraidevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"
#include "engine/egifthelpers.h"
#include "eraidresourceevent.h"

ePlayerRaidEvent::ePlayerRaidEvent(
        const eGameEventBranch branch,
        eGameBoard& board) :
    ePlayerConquestEventBase(eGameEventType::playerRaidEvent,
                             branch, board) {
    board.addConquest(this);
}

void ePlayerRaidEvent::initialize(
        const eEnlistedForces& forces,
        const stdsptr<eWorldCity>& city,
        const eResourceType resource) {
    mForces = forces;
    mCity = city;
    mResource = resource;
}

void ePlayerRaidEvent::trigger() {
    auto& board = getBoard();
    board.removeConquest(this);
    if(!mCity) return;

    const int enemyStr = mCity->strength();
    const int str = mForces.strength();

    const double killFrac = std::clamp(0.5*enemyStr/str, 0., 1.);
    mForces.kill(killFrac);

    if(str > 0.75*enemyStr) {
        const int oA = mCity->army();
        const int nA = std::clamp(oA - 1, 1, 5);
        mCity->setArmy(nA);
    }

    const bool raided = str > 0.75*enemyStr;
    eEventData ed;
    ed.fCity = mCity;
    const auto rel = mCity->relationship();
    if(rel == eWorldCityRelationship::ally) {
        auto& worldBoard = board.getWorldBoard();
        worldBoard.attackedAlly();
        board.event(eEvent::allyAttackedByPlayer, ed);
    }
    if(raided) {
        eResourceType res = mResource;
        if(res == eResourceType::none) {
            if(rand() % 2) {
                res = eResourceType::drachmas;
            } else {
                const auto& sells = mCity->sells();
                if(sells.empty()) {
                    res = eResourceType::drachmas;
                } else {
                    const int ss = sells.size();
                    res = sells[rand() % ss].fType;
                }
            }
        }
        const int count = 2*eGiftHelpers::giftCount(res);
        const auto e = e::make_shared<eRaidResourceEvent>(
                           eGameEventBranch::child, board);
        const auto boardDate = board.date();
        const int period = 75;
        const auto date = boardDate + period;
        e->initializeDate(date, period, 1);
        e->initialize(true, res, count, mCity);
        addConsequence(e);
    } else {
        board.event(eEvent::cityRaidFailed, ed);
    }

    postTrigger();
}

std::string ePlayerRaidEvent::longName() const {
    return eLanguage::text("player_raid_event_long_name");
}

void ePlayerRaidEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    mForces.write(dst);
    dst.writeCity(mCity.get());
    dst << mResource;
}

void ePlayerRaidEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    auto& board = getBoard();
    mForces.read(board, src);
    src.readCity(&board, [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
    src >> mResource;
}

stdsptr<eGameEvent> ePlayerRaidEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<ePlayerRaidEvent>(branch(), getBoard());
    c->mForces = mForces;
    c->mCity = mCity;
    c->mResource = mResource;
    c->setReason(reason);
    return c;
}
