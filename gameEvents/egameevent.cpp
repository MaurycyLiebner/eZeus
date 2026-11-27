#include "egameevent.h"

#include "engine/egameboard.h"

#include "egodvisitevent.h"
#include "egodattackevent.h"
#include "emonsterunleashedevent.h"
#include "emonsterinvasionevent.h"
#include "emonsterincityevent.h"
#include "einvasionevent.h"
#include "epaytributeevent.h"
#include "emakerequestevent.h"
#include "ereceiverequestevent.h"
#include "egifttoevent.h"
#include "egiftfromevent.h"
#include "egodquestevent.h"
#include "egodquestfulfilledevent.h"
#include "eplayerconquestevent.h"
#include "eplayerraidevent.h"
#include "eraidresourceevent.h"
#include "earmyreturnevent.h"
#include "emilitarychangeevent.h"
#include "eeconomicchangeevent.h"
#include "etroopsrequestevent.h"
#include "etroopsrequestfulfilledevent.h"
#include "egoddisasterevent.h"
#include "egodtraderesumesevent.h"
#include "erequestaidevent.h"
#include "erequeststrikeevent.h"
#include "erivalarmyawayevent.h"
#include "eearthquakeevent.h"
#include "elavaevent.h"
#include "etidalwaveevent.h"
#include "esinklandevent.h"
#include "elandslideevent.h"
#include "ecitybecomesevent.h"
#include "etradeshutdownevent.h"
#include "etradeopenupevent.h"
#include "esupplychangeevent.h"
#include "edemandchangeevent.h"
#include "epricechangeevent.h"
#include "ewagechangeevent.h"
#include "ereinforcementsevent.h"

eGameEvent::eGameEvent(const eCityId cid,
                       const eGameEventType type,
                       const eGameEventBranch branch,
                       eGameBoard& board) :
    mCid(cid), mType(type), mBranch(branch), mBoard(board) {
    mBoard.addGameEvent(this);

    const auto e4 = eLanguage::text("base_trigger");
    mBaseTrigger = e::make_shared<eEventTrigger>(cid, e4, board);
    addTrigger(mBaseTrigger);
}

eGameEvent::~eGameEvent() {
    mBoard.removeGameEvent(this);
}

stdsptr<eGameEvent> eGameEvent::makeCopy() const {
    const size_t size = 1000000;
    void* mem = malloc(size);
    {
        worldBoard()->setIOIDs();
        eWriteTarget target(mem);
        eWriteStream dst(target);
        dst.writeFormat("eZeus");
        write(dst);
    }
    const auto result = sCreate(mCid, mType, mBranch, mBoard);
    {
        eReadSource source(mem);
        eReadStream src(source);
        src.readFormat();
        result->read(src);
        src.handlePostFuncs();
    }

    free(mem);

    return result;
}

stdsptr<eGameEvent> eGameEvent::sCreate(
        const eCityId cid,
        const eGameEventType type,
        const eGameEventBranch branch,
        eGameBoard& board) {
    switch(type) {
    case eGameEventType::godVisit:
        return e::make_shared<eGodVisitEvent>(cid, branch, board);
    case eGameEventType::godAttack:
        return e::make_shared<eGodAttackEvent>(cid, branch, board);
    case eGameEventType::monsterUnleashed:
        return e::make_shared<eMonsterUnleashedEvent>(cid, branch, board);
    case eGameEventType::monsterInvasion:
        return e::make_shared<eMonsterInvasionEvent>(cid, branch, board);
    case eGameEventType::monsterInvasionWarning:
        return nullptr;
    case eGameEventType::monsterInCity:
        return e::make_shared<eMonsterInCityEvent>(cid, branch, board);
    case eGameEventType::invasion:
        return e::make_shared<eInvasionEvent>(cid, branch, board);
    case eGameEventType::invasionWarning:
        return nullptr;
    case eGameEventType::payTribute:
        return e::make_shared<ePayTributeEvent>(cid, branch, board);
    case eGameEventType::makeRequest:
        return e::make_shared<eMakeRequestEvent>(cid, branch, board);
    case eGameEventType::receiveRequest:
        return e::make_shared<eReceiveRequestEvent>(cid, branch, board);
    case eGameEventType::giftTo:
        return e::make_shared<eGiftToEvent>(cid, branch, board);
    case eGameEventType::giftFrom:
        return e::make_shared<eGiftFromEvent>(cid, branch, board);
    case eGameEventType::godQuest:
        return e::make_shared<eGodQuestEvent>(cid, branch, board);
    case eGameEventType::godQuestFulfilled:
        return e::make_shared<eGodQuestFulfilledEvent>(cid, branch, board);
    case eGameEventType::playerConquestEvent:
        return e::make_shared<ePlayerConquestEvent>(cid, branch, board);
    case eGameEventType::raidResourceReceive:
        return e::make_shared<eRaidResourceEvent>(cid, branch, board);
    case eGameEventType::playerRaidEvent:
        return e::make_shared<ePlayerRaidEvent>(cid, branch, board);
    case eGameEventType::armyReturnEvent:
        return e::make_shared<eArmyReturnEvent>(cid, branch, board);
    case eGameEventType::economicChange:
        return e::make_shared<eEconomicChangeEvent>(cid, branch, board);
    case eGameEventType::militaryChange:
        return e::make_shared<eMilitaryChangeEvent>(cid, branch, board);

    case eGameEventType::troopsRequest:
        return e::make_shared<eTroopsRequestEvent>(cid, branch, board);
    case eGameEventType::troopsRequestFulfilled:
        return e::make_shared<eTroopsRequestFulfilledEvent>(cid, branch, board);

    case eGameEventType::godDisaster:
        return e::make_shared<eGodDisasterEvent>(cid, branch, board);
    case eGameEventType::godTradeResumes:
        return e::make_shared<eGodTradeResumesEvent>(cid, branch, board);

    case eGameEventType::requestAid:
        return e::make_shared<eRequestAidEvent>(cid, branch, board);
    case eGameEventType::requestStrike:
        return e::make_shared<eRequestStrikeEvent>(cid, branch, board);

    case eGameEventType::rivalArmyAway:
        return e::make_shared<eRivalArmyAwayEvent>(cid, branch, board);

    case eGameEventType::earthquake:
        return e::make_shared<eEarthquakeEvent>(cid, branch, board);
    case eGameEventType::lavaFlow:
        return e::make_shared<eLavaEvent>(cid, branch, board);
    case eGameEventType::tidalWave:
        return e::make_shared<eTidalWaveEvent>(cid, branch, board);
    case eGameEventType::sinkLand:
        return e::make_shared<eSinkLandEvent>(cid, branch, board);
    case eGameEventType::landSlide:
        return e::make_shared<eLandSlideEvent>(cid, branch, board);

    case eGameEventType::cityBecomes:
        return e::make_shared<eCityBecomesEvent>(cid, branch, board);

    case eGameEventType::tradeShutdowns:
        return e::make_shared<eTradeShutDownEvent>(cid, branch, board);
    case eGameEventType::tradeOpensUp:
        return e::make_shared<eTradeOpenUpEvent>(cid, branch, board);

    case eGameEventType::supplyChange:
        return e::make_shared<eSupplyChangeEvent>(cid, branch, board);
    case eGameEventType::demandChange:
        return e::make_shared<eDemandChangeEvent>(cid, branch, board);

    case eGameEventType::priceChange:
        return e::make_shared<ePriceChangeEvent>(cid, branch, board);
    case eGameEventType::wageChange:
        return e::make_shared<eWageChangeEvent>(cid, branch, board);

    case eGameEventType::reinforcementsEvent:
        return e::make_shared<eReinforcementsEvent>(cid, branch, board);
    }
    return nullptr;
}

ePlayerId eGameEvent::playerId() const {
    return mBoard.cityIdToPlayerId(mCid);
}

bool eGameEvent::isOnBoard() const {
    return mBoard.boardCityWithId(mCid);
}

bool eGameEvent::isPersonPlayer() const {
    return mBoard.personPlayer() == playerId();
}

void eGameEvent::setupStartDate(const eDate& currentDate) {
    mNextDate = currentDate;
    const int years = chooseYear();
    mNextDate.nextYears(years);
    mNextDate.nextMonths(mDatePlusMonths);
    bool nextMonth;
    bool nextYear;
    mNextDate.nextDays(mDatePlusDays, nextMonth, nextYear);
    updateWarningDates();
}

void eGameEvent::initializeDate(const eDate& startDate,
                                const int period,
                                const int nRuns) {
    mNextDate = startDate;
    updateWarningDates();
    setPeriodMin(period);
    setPeriodMax(period);
    setRepeat(nRuns);
}

void eGameEvent::addWarning(const stdsptr<eWarning>& w) {
    mWarnings.emplace_back(w);
}

void eGameEvent::clearWarnings() {
    mWarnings.clear();
}

bool eGameEvent::isMainEvent() const {
    return mBranch != eGameEventBranch::child;
}

bool eGameEvent::isRootEvent() const {
    return mBranch == eGameEventBranch::root;
}

bool eGameEvent::isTriggerEvent() const {
    return mBranch == eGameEventBranch::trigger;
}

bool eGameEvent::isChildEvent() const {
    return mBranch == eGameEventBranch::child;
}

void eGameEvent::addConsequence(const stdsptr<eGameEvent>& event) {
    mConsequences.push_back(event);
    if(event->branch() == eGameEventBranch::child) {
        event->setReason(reason());
    }
    event->mParent = this;
}

void eGameEvent::clearConsequences() {
    mConsequences.clear();
}

bool eGameEvent::hasActiveConsequences() const {
    for(const auto& c : mConsequences) {
        if(!c->finished()) return true;
        if(c->hasActiveConsequences()) return true;
    }
    return false;
}

std::string eGameEvent::longDatedName() const {
    auto dateStr = "+" + std::to_string(mDatePlusYearsMin) +
                   "-" + std::to_string(mDatePlusYearsMax);
    dateStr += "  +" + std::to_string(mDatePlusMonths);
    dateStr += "  +" + std::to_string(mDatePlusDays);
    const auto eventName = longName();
    return dateStr + "  |  " + eventName;
}

void eGameEvent::setReason(const std::string& r) {
    mReason = r;
}

void eGameEvent::setWarningMonths(const int ms) {
    mWarningMonths = ms;
}

int eGameEvent::choosePeriod() const {
    int periodDays = mPeriodDaysMin;
    if(mPeriodDaysMax > mPeriodDaysMin) {
        periodDays += eRand::rand() % (mPeriodDaysMax - mPeriodDaysMin);
    }
    return periodDays;
}

int eGameEvent::chooseYear() const {
    int years = mDatePlusYearsMin;
    if(mDatePlusYearsMax > mDatePlusYearsMin) {
        years += eRand::rand() % (mDatePlusYearsMax - mDatePlusYearsMin);
    }
    return years;
}

void eGameEvent::setRepeat(const int r) {
    mRemNRuns = r;
}

void eGameEvent::handleNewDate(const eDate& date) {
    if(mEpisodeCompleteEvent) return;
    for(const auto& c : mConsequences) {
        c->handleNewDate(date);
    }
    if(mRemNRuns <= 0) return;
    for(const auto& w : mWarnings) {
        w->handleNewDate(date);
    }
    if(date > mNextDate) {
        trigger();
        mRemNRuns--;
        const int periodDays = choosePeriod();
        mNextDate = date + periodDays;
        updateWarningDates();
        callBaseTrigger();
    }
}

int eGameEvent::triggerEventsCount() const {
    int r = 0;
    for(const auto& t : mTriggers) {
        r += t->eventCount();
    }
    return r;
}

eWorldBoard* eGameEvent::worldBoard() const {
    return &mBoard.world();
}

void eGameEvent::startingNewEpisode() {
    if(mEpisodeEvent) {
        setRepeat(0);
    }
    for(const auto& c : mConsequences) {
        c->startingNewEpisode();
    }
}

void eGameEvent::addTrigger(const stdsptr<eEventTrigger>& et) {
    mTriggers.push_back(et);
}

void eGameEvent::callBaseTrigger() {
    const auto board = gameBoard();
    if(!board) return;
    const auto date = board->date();
    mBaseTrigger->trigger(*this, date, "");
}

void eGameEvent::updateWarningDates() {
    const auto& board = *gameBoard();
    const auto currentDate = board.date();
    for(const auto& w : mWarnings) {
        const int ms = w->warningMonths();
        if(ms > mWarningMonths ||
           (ms == mWarningMonths &&
            !w->isInitialWarning())) {
            w->setFinished(true);
            continue;
        }
        auto wdate = mNextDate;
        wdate.prevMonths(ms);
        w->setNextDate(wdate);
        if(wdate < currentDate) {
            w->setFinished(true);
        }
    }
}

void eGameEvent::write(eWriteStream& dst) const {
    dst << mIOID;
    dst << mDatePlusDays;
    dst << mDatePlusMonths;
    dst << mDatePlusYearsMin;
    dst << mDatePlusYearsMax;
    mNextDate.write(dst);
    dst << mPeriodDaysMin;
    dst << mPeriodDaysMax;
    dst << mWarningMonths;
    dst << mRemNRuns;
    dst << mReason;
    dst << mEpisodeCompleteEvent;

    for(const auto& w : mWarnings) {
        w->write(dst);
    }

    dst << mConsequences.size();
    for(const auto& c : mConsequences) {
        dst << c->type();
        dst << c->branch();
        c->write(dst);
    }

    for(const auto& et : mTriggers) {
        et->write(dst);
    }

    dst << mEpisodeEvent;
}

void eGameEvent::read(eReadStream& src) {
    src >> mIOID;
    src >> mDatePlusDays;
    src >> mDatePlusMonths;
    src >> mDatePlusYearsMin;
    src >> mDatePlusYearsMax;
    mNextDate.read(src);
    src >> mPeriodDaysMin;
    src >> mPeriodDaysMax;
    src >> mWarningMonths;
    src >> mRemNRuns;
    src >> mReason;
    src >> mEpisodeCompleteEvent;

    for(const auto& w : mWarnings) {
        w->read(src);
    }

    int ncs;
    src >> ncs;
    for(int i = 0; i < ncs; i++) {
        eGameEventType type;
        src >> type;
        eGameEventBranch branch;
        src >> branch;
        const auto e = eGameEvent::sCreate(mCid, type, branch, mBoard);
        e->read(src);
        addConsequence(e);
    }

    for(const auto& et : mTriggers) {
        et->read(src);
    }

    src >> mEpisodeEvent;
}

void eGameEvent::loadResources() const {
    for(const auto& e : mConsequences) {
        e->loadResources();
    }
    for(const auto& et : mTriggers) {
        et->loadResources();
    }
}
