#include "etroopsrequestevent.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "emessages.h"
#include "engine/ecityrequest.h"

#include "etroopsrequestfulfilledevent.h"

eTroopsRequestEvent::eTroopsRequestEvent(const eGameEventBranch branch) :
    eGameEvent(eGameEventType::troopsRequest, branch) {
    const auto e1 = eLanguage::text("early");
    mEarlyTrigger = e::make_shared<eEventTrigger>(e1);
    const auto e2 = eLanguage::text("comply");
    mComplyTrigger = e::make_shared<eEventTrigger>(e2);
    const auto e3 = eLanguage::text("too_late");
    mTooLateTrigger = e::make_shared<eEventTrigger>(e3);
    const auto e4 = eLanguage::text("refuse");
    mRefuseTrigger = e::make_shared<eEventTrigger>(e4);
    const auto e5 = eLanguage::text("lost_battle");
    mLostBattleTrigger = e::make_shared<eEventTrigger>(e5);

    addTrigger(mEarlyTrigger);
    addTrigger(mComplyTrigger);
    addTrigger(mTooLateTrigger);
    addTrigger(mRefuseTrigger);
    addTrigger(mLostBattleTrigger);
}

eTroopsRequestEvent::~eTroopsRequestEvent() {
    const auto board = gameBoard();
    if(board) board->removeCityTroopsRequest(this);
}

void eTroopsRequestEvent::initialize(
        const int postpone,
        const stdsptr<eWorldCity> &c,
        const stdsptr<eWorldCity> &rival,
        const bool finish) {
    mPostpone = postpone;
    mCity = c;
    mRivalCity = rival;
    mFinish = finish;
}

std::string eTroopsRequestEvent::longName() const {
    auto tmpl = eLanguage::text("troops_request_long_name");
    const auto none = eLanguage::text("none");
    const auto ctstr = mCity ? mCity->name() : none;
    eStringHelpers::replace(tmpl, "%1", ctstr);
    return tmpl;
}

void eTroopsRequestEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mFinish;
    dst << mPostpone;
    dst.writeCity(mCity.get());
    dst.writeCity(mRivalCity.get());
}

void eTroopsRequestEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mFinish;
    src >> mPostpone;
    src.readCity(worldBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
    src.readCity(worldBoard(), [this](const stdsptr<eWorldCity>& c) {
        mRivalCity = c;
    });
}

void eTroopsRequestEvent::setCity(const stdsptr<eWorldCity>& c) {
    mCity = c;
}

void eTroopsRequestEvent::setRivalCity(const stdsptr<eWorldCity>& c) {
    mRivalCity = c;
}

const int gPostponeDays = 6*31;

void eTroopsRequestEvent::trigger() {
    if(!mCity) return;
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fCity = mCity;
    ed.fRivalCity = mRivalCity;
    ed.fTime = 6;
    ed.fA0Key = eLanguage::zeusText(44, 275);
    ed.fA1Key = eLanguage::zeusText(44, 211);
    ed.fA2Key = eLanguage::zeusText(44, 212);

    if(mFinish) {
        if(mPostpone > 2) {
            lost();
        } else {
            won();
        }
        return;
    }

    ed.fCA0 = [this](const eAction& close) { // dispatch now
        dispatch(close);
    };

    if(mPostpone < 2) {
        ed.fA1 = [this, board]() { // postpone
            const auto e = e::make_shared<eTroopsRequestEvent>(
                               eGameEventBranch::child);
            e->initialize(mPostpone + 1, mCity, mRivalCity);
            const auto date = board->date() + gPostponeDays;
            e->initializeDate(date);
            addConsequence(e);
        };
    }

    ed.fA2 = [this, board]() { // refuse
        board->removeCityTroopsRequest(mainEvent<eTroopsRequestEvent>());
        const auto e = e::make_shared<eTroopsRequestEvent>(
                           eGameEventBranch::child);
        e->initialize(5, mCity, mRivalCity, true);
        const auto date = board->date() + 31;
        e->initializeDate(date);
        addConsequence(e);
    };


    ed.fType = eMessageEventType::troopsRequest;
    if(mPostpone == 0) { // initial
        board->addCityTroopsRequest(mainEvent<eTroopsRequestEvent>());
    }
    if(mCity->isVassal()) {
        if(mPostpone == 0) { // initial
            board->event(eEvent::troopsRequestVassalInitial, ed);
        } else if(mPostpone == 1) { // reminder
            board->event(eEvent::troopsRequestVassalFirstReminder, ed);
        } else if(mPostpone == 2) { // overdue
            board->event(eEvent::troopsRequestVassalLastReminder, ed);
        }
    } else if(mCity->isColony()) {
        if(mPostpone == 0) { // initial
            board->event(eEvent::troopsRequestColonyInitial, ed);
        } else if(mPostpone == 1) { // reminder
            board->event(eEvent::troopsRequestColonyFirstReminder, ed);
        } else if(mPostpone == 2) { // overdue
            board->event(eEvent::troopsRequestColonyLastReminder, ed);
        }
    } else if(mCity->isParentCity()) {
        if(mPostpone == 0) { // initial
            board->event(eEvent::troopsRequestParentCityInitial, ed);
        } else if(mPostpone == 1) { // reminder
            board->event(eEvent::troopsRequestParentCityFirstReminder, ed);
        } else if(mPostpone == 2) { // overdue
            board->event(eEvent::troopsRequestParentCityLastReminder, ed);
        }
    } else { // ally
        if(mPostpone == 0) { // initial
            board->event(eEvent::troopsRequestAllyInitial, ed);
        } else if(mPostpone == 1) { // reminder
            board->event(eEvent::troopsRequestAllyFirstReminder, ed);
        } else if(mPostpone == 2) { // overdue
            board->event(eEvent::troopsRequestAllyLastReminder, ed);
        }
    }
}

void eTroopsRequestEvent::dispatch(const eAction& close) {
    const auto board = gameBoard();
    if(!board) return;
    board->requestForces([this, board, close](
                         const eEnlistedForces& f,
                         const eResourceType) {
        board->enlistForces(f);
        board->removeCityTroopsRequest(mainEvent<eTroopsRequestEvent>());
        const auto e = e::make_shared<eTroopsRequestFulfilledEvent>(
                           eGameEventBranch::child, board);
        const auto currentDate = board->date();
        e->initialize(f, mCity, mRivalCity);
        const auto edate = currentDate + 3*31;
        e->initializeDate(edate);
        clearConsequences();
        addConsequence(e);
        if(close) close();
    }, {}, {mCity, mRivalCity});
}

void eTroopsRequestEvent::won() {
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fCity = mCity;
    ed.fRivalCity = mRivalCity;
    ed.fType = eMessageEventType::common;

    auto& msgs = eMessages::instance;
    eTroopsRequestedMessages* rrmsgs = nullptr;
    if(mCity->isVassal()) {
        rrmsgs = &msgs.fVassalTroopsRequest;
    } else if(mCity->isColony()) {
        rrmsgs = &msgs.fColonyTroopsRequest;
    } else if(mCity->isParentCity()) {
        rrmsgs = &msgs.fParentCityTroopsRequest;
    } else { // ally
        rrmsgs = &msgs.fAllyTroopsRequest;
    }
    board->event(eEvent::troopsRequestAttackAverted, ed);
    mCity->incAttitude(10);

    const auto& reason = rrmsgs->fComplyReason;
    const auto me = mainEvent<eTroopsRequestEvent>();
    me->finished(*me->mComplyTrigger, reason);
}

void eTroopsRequestEvent::lost() {
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fCity = mCity;
    ed.fRivalCity = mRivalCity;
    ed.fType = eMessageEventType::common;


    auto& msgs = eMessages::instance;
    eEvent event;
    eTroopsRequestedMessages* rrmsgs = nullptr;
    if(mCity->isVassal()) {
        event = eEvent::troopsRequestVassalConquered;
        rrmsgs = &msgs.fVassalTroopsRequest;
    } else if(mCity->isColony()) {
        event = eEvent::troopsRequestColonyConquered;
        rrmsgs = &msgs.fColonyTroopsRequest;
    } else if(mCity->isParentCity()) {
        event = eEvent::troopsRequestParentCityConquered;
        rrmsgs = &msgs.fParentCityTroopsRequest;
    } else { // ally
        event = eEvent::troopsRequestAllyConquered;
        rrmsgs = &msgs.fAllyTroopsRequest;
    }
    board->event(event, ed);
    mCity->incAttitude(-25);
    mCity->setRelationship(eForeignCityRelationship::rival);
    mCity->setConqueredBy(mRivalCity);

    const auto& reason = rrmsgs->fLostBattleReason;
    const auto me = mainEvent<eTroopsRequestEvent>();
    me->finished(*me->mLostBattleTrigger, reason);
}

void eTroopsRequestEvent::finished(eEventTrigger& t, const eReason& r) {
    const auto board = gameBoard();
    if(!board) return;
    const auto date = board->date();
    t.trigger(*this, date, r.fFull);
}
