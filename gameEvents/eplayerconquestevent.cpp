#include "eplayerconquestevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"
#include "earmyreturnevent.h"

ePlayerConquestEvent::ePlayerConquestEvent(
        const eGameEventBranch branch,
        eGameBoard& board) :
    eGameEvent(eGameEventType::playerConquestEvent, branch, board) {}

void ePlayerConquestEvent::initialize(
        const eEnlistedForces& forces,
        const stdsptr<eWorldCity>& city) {
    mForces = forces;
    mCity = city;
}

void ePlayerConquestEvent::trigger() {
    if(!mCity) return;
    auto& board = getBoard();

    const int enemyStr = (10 + (rand() % 3))*mCity->army();

    int str = 0;
    for(const auto& s : mForces.fSoldiers) {
        double mult = 1.;
        switch(s->type()) {
        case eBannerType::horseman:
            mult = 1.5;
            break;
        default:
            break;
        }

        str += std::floor(mult*s->count());
    }
    for(const auto& c : mForces.fAllies) {
        str += 3*c->army();
    }
    str += 10*mForces.fHeroes.size();

    const double killFrac = std::clamp(0.5*enemyStr/str, 0., 1.);

    for(const auto& s : mForces.fSoldiers) {
        const int oC = s->count();
        int nC = std::round((1 - killFrac)*oC);
        nC = std::clamp(nC, 0, 8);
        for(int i = nC; i < oC; i++) {
            s->decCount();
        }
    }

    for(const auto& c : mForces.fAllies) {
        const int oA = c->army();
        const int nA = std::clamp(oA - 1, 1, 5);
        c->setArmy(nA);
    }

    if(str > 0.75*enemyStr) {
        const int oA = mCity->army();
        const int nA = std::clamp(oA - 1, 1, 5);
        mCity->setArmy(nA);
    }

    const bool conquered = str > enemyStr;

    eEventData ed;
    ed.fCity = mCity;
    if(conquered) {
        board.event(eEvent::cityConquered, ed);
    } else {
        board.event(eEvent::cityConquerFailed, ed);
    }

    const auto e = e::make_shared<eArmyReturnEvent>(
                       eGameEventBranch::child, board);
    const auto boardDate = board.date();
    const int period = 150;
    const auto date = boardDate + period;
    e->initializeDate(date, period, 1);
    e->initialize(mForces, mCity);
    addConsequence(e);
}

std::string ePlayerConquestEvent::longName() const {
    return eLanguage::text("player_conquest_event_long_name");
}

void ePlayerConquestEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    mForces.write(dst);
    dst.writeCity(mCity.get());
}

void ePlayerConquestEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    auto& board = getBoard();
    mForces.read(board, src);
    src.readCity(&board, [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}

stdsptr<eGameEvent> ePlayerConquestEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<ePlayerConquestEvent>(branch(), getBoard());
    c->mForces = mForces;
    c->mCity = mCity;
    c->setReason(reason);
    return c;
}
