#include "ereceiverequestevent.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "emessages.h"
#include "engine/ecityrequest.h"

eReceiveRequestEvent::eReceiveRequestEvent(const eGameEventBranch branch) :
    eGameEvent(eGameEventType::receiveRequest, branch) {
    const auto e1 = eLanguage::text("early");
    mEarlyTrigger = e::make_shared<eEventTrigger>(e1);
    const auto e2 = eLanguage::text("comply");
    mComplyTrigger = e::make_shared<eEventTrigger>(e2);
    const auto e3 = eLanguage::text("too_late");
    mTooLateTrigger = e::make_shared<eEventTrigger>(e3);
    const auto e4 = eLanguage::text("refuse");
    mRefuseTrigger = e::make_shared<eEventTrigger>(e4);

    addTrigger(mEarlyTrigger);
    addTrigger(mComplyTrigger);
    addTrigger(mTooLateTrigger);
    addTrigger(mRefuseTrigger);
}

eReceiveRequestEvent::~eReceiveRequestEvent() {
    const auto board = gameBoard();
    if(board) board->removeCityRequest(this);
}

void eReceiveRequestEvent::initialize(
        const int postpone,
        const eResourceType res,
        const int count,
        const stdsptr<eWorldCity> &c,
        const bool finish) {
    mPostpone = postpone;
    mResource = res;
    mCount = count;
    mCity = c;
    mFinish = finish;
}

const int gPostponeDays = 6*31;

void eReceiveRequestEvent::trigger() {
    if(!mCity) return;
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fCity = mCity;
    ed.fResourceType = mResource;
    ed.fResourceCount = mCount;
    ed.fTime = 6;
    ed.fA0Key = eLanguage::zeusText(44, 275);
    ed.fA1Key = eLanguage::zeusText(44, 211);
    ed.fA2Key = eLanguage::zeusText(44, 212);

    if(mFinish) {
        auto& msgs = eMessages::instance;
        if(mPostpone > 1) {
            ed.fType = eMessageEventType::resourceGranted;
            eEvent event;
            eReceiveRequestMessages* rrmsgs = nullptr;
            if(mCity->isRival()) {
                event = eEvent::generalRequestRivalTooLate;
                rrmsgs = &msgs.fGeneralRequestRivalD;
            } else if(mCity->isVassal() || mCity->isColony()) {
                event = eEvent::generalRequestSubjectTooLate;
                rrmsgs = &msgs.fGeneralRequestSubjectP;
            } else if(mCity->isParentCity()) {
                event = eEvent::generalRequestParentTooLate;
                rrmsgs = &msgs.fGeneralRequestParentR;
            } else { // ally
                event = eEvent::generalRequestAllyTooLate;
                rrmsgs = &msgs.fGeneralRequestAllyS;
            }
            board->event(event, ed);
            mCity->incAttitude(-5);

            const auto& reason = rrmsgs->fTooLateReason;
            const auto me = mainEvent<eReceiveRequestEvent>();
            me->finished(*me->mTooLateTrigger, reason);
        } else {
            ed.fType = eMessageEventType::resourceGranted;
            eEvent event;
            eReceiveRequestMessages* rrmsgs = nullptr;
            if(mCity->isRival()) {
                event = eEvent::generalRequestRivalComply;
                rrmsgs = &msgs.fGeneralRequestRivalD;
            } else if(mCity->isVassal() || mCity->isColony()) {
                event = eEvent::generalRequestSubjectComply;
                rrmsgs = &msgs.fGeneralRequestSubjectP;
            } else if(mCity->isParentCity()) {
                event = eEvent::generalRequestParentComply;
                rrmsgs = &msgs.fGeneralRequestParentR;
            } else { // ally
                event = eEvent::generalRequestAllyComply;
                rrmsgs = &msgs.fGeneralRequestAllyS;
            }
            board->event(event, ed);
            mCity->incAttitude(10);

            const auto& reason = rrmsgs->fComplyReason;
            const auto me = mainEvent<eReceiveRequestEvent>();
            me->finished(*me->mComplyTrigger, reason);
        }
        return;
    }

    if(mPostpone > 3) {
        ed.fType = eMessageEventType::resourceGranted;
        eEvent event;
        eReceiveRequestMessages* rrmsgs = nullptr;
        auto& msgs = eMessages::instance;
        if(mCity->isRival()) {
            event = eEvent::generalRequestRivalRefuse;
            rrmsgs = &msgs.fGeneralRequestRivalD;
        } else if(mCity->isVassal() || mCity->isColony()) {
            event = eEvent::generalRequestSubjectRefuse;
            rrmsgs = &msgs.fGeneralRequestSubjectP;
        } else if(mCity->isParentCity()) {
            event = eEvent::generalRequestParentRefuse;
            rrmsgs = &msgs.fGeneralRequestParentR;
        } else { // ally
            event = eEvent::generalRequestAllyRefuse;
            rrmsgs = &msgs.fGeneralRequestAllyS;
        }
        board->event(event, ed);
        mCity->incAttitude(-15);

        auto& reason = rrmsgs->fRefuseReason;
        const auto me = mainEvent<eReceiveRequestEvent>();
        me->finished(*me->mRefuseTrigger, reason);
        return;
    }

    const int avCount = board->resourceCount(mResource);
    ed.fSpaceCount = avCount;

    if(avCount >= mCount) {
        ed.fA0 = [this]() { // dispatch now
            dispatch();
        };
    }

    if(mPostpone < 3) {
        ed.fA1 = [this, board]() { // postpone
            const auto e = e::make_shared<eReceiveRequestEvent>(
                               eGameEventBranch::child);
            e->initialize(mPostpone + 1, mResource, mCount, mCity);
            const auto date = board->date() + gPostponeDays;
            e->initializeDate(date);
            addConsequence(e);
        };
    }

    ed.fA2 = [this, board]() { // refuse
        board->removeCityRequest(mainEvent<eReceiveRequestEvent>());
        const auto e = e::make_shared<eReceiveRequestEvent>(
                           eGameEventBranch::child);
        e->initialize(5, mResource, mCount, mCity);
        const auto date = board->date() + 31;
        e->initializeDate(date);
        addConsequence(e);
    };


    ed.fType = eMessageEventType::generalRequestGranted;
    if(mPostpone == 0) { // initial
        board->addCityRequest(mainEvent<eReceiveRequestEvent>());
    }
    if(mCity->isRival()) {
        if(mPostpone == 0) { // initial
            board->event(eEvent::generalRequestRivalInitial, ed);
        } else if(mPostpone == 1) { // reminder
            board->event(eEvent::generalRequestRivalReminder, ed);
        } else if(mPostpone == 2) { // overdue
            board->event(eEvent::generalRequestRivalOverdue, ed);
        } else if(mPostpone == 3) { // warning
            board->event(eEvent::generalRequestRivalWarning, ed);
        }
    } else if(mCity->isVassal() || mCity->isColony()) {
        if(mPostpone == 0) { // initial
            board->event(eEvent::generalRequestSubjectInitial, ed);
        } else if(mPostpone == 1) { // reminder
            board->event(eEvent::generalRequestSubjectReminder, ed);
        } else if(mPostpone == 2) { // overdue
            board->event(eEvent::generalRequestSubjectOverdue, ed);
        } else if(mPostpone == 3) { // warning
            board->event(eEvent::generalRequestSubjectWarning, ed);
        }
    } else if(mCity->isParentCity()) {
        if(mPostpone == 0) { // initial
            board->event(eEvent::generalRequestParentInitial, ed);
        } else if(mPostpone == 1) { // reminder
            board->event(eEvent::generalRequestParentReminder, ed);
        } else if(mPostpone == 2) { // overdue
            board->event(eEvent::generalRequestParentOverdue, ed);
        } else if(mPostpone == 3) { // warning
            board->event(eEvent::generalRequestParentWarning, ed);
        }
    } else { // ally
        if(mPostpone == 0) { // initial
            board->event(eEvent::generalRequestAllyInitial, ed);
        } else if(mPostpone == 1) { // reminder
            board->event(eEvent::generalRequestAllyReminder, ed);
        } else if(mPostpone == 2) { // overdue
            board->event(eEvent::generalRequestAllyOverdue, ed);
        } else if(mPostpone == 3) { // warning
            board->event(eEvent::generalRequestAllyWarning, ed);
        }
    }
}

std::string eReceiveRequestEvent::longName() const {
    auto tmpl = eLanguage::text("receive_request");
    const auto resName = eResourceTypeHelpers::typeName(mResource);
    const auto cStr = std::to_string(mCount);
    eStringHelpers::replace(tmpl, "%1", cStr + " " + resName);
    const auto none = eLanguage::text("none");
    const auto ctstr = mCity ? mCity->name() : none;
    eStringHelpers::replace(tmpl, "%2", ctstr);
    return tmpl;
}

void eReceiveRequestEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mFinish;
    dst << mPostpone;
    dst << mResource;
    dst << mCount;
    dst.writeCity(mCity.get());
}

void eReceiveRequestEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mFinish;
    src >> mPostpone;
    src >> mResource;
    src >> mCount;
    src.readCity(worldBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}

stdsptr<eGameEvent> eReceiveRequestEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eReceiveRequestEvent>(
                       branch());
    c->setGameBoard(gameBoard());
    c->setWorldBoard(worldBoard());
    c->initialize(mPostpone, mResource, mCount, mCity, mFinish);
    c->setReason(reason);
    return c;
}

void eReceiveRequestEvent::setCity(const stdsptr<eWorldCity>& c) {
    mCity = c;
}

void eReceiveRequestEvent::setResourceType(const eResourceType type) {
    mResource = type;
}

void eReceiveRequestEvent::setResourceCount(const int c) {
    mCount = c;
}

eCityRequest eReceiveRequestEvent::cityRequest() const {
    eCityRequest request;
    request.fCity = mCity;
    request.fType = mResource;
    request.fCount = mCount;
    return request;
}

void eReceiveRequestEvent::dispatch() {
    const auto board = gameBoard();
    if(!board) return;
    board->takeResource(mResource, mCount);
    fulfillWithoutCost();
}

void eReceiveRequestEvent::fulfillWithoutCost() {
    const auto board = gameBoard();
    if(!board) return;
    board->removeCityRequest(mainEvent<eReceiveRequestEvent>());
    const auto e = e::make_shared<eReceiveRequestEvent>(*this);
    int postpone = mPostpone - 1;
    auto date = startDate();
    const auto currentDate = board->date();
    while(date <= currentDate) {
        date += gPostponeDays;
        postpone++;
    }
    e->initialize(postpone, mResource, mCount, mCity, true);
    const auto edate = currentDate + 3*31;
    e->initializeDate(edate);
    clearConsequences();
    addConsequence(e);
}

void eReceiveRequestEvent::finished(eEventTrigger& t, const eReason& r) {
    const auto board = gameBoard();
    if(!board) return;
    const auto date = board->date();
    auto rFull = r.fFull;
    const auto amount = std::to_string(mCount);
    eStringHelpers::replaceAll(rFull, "[amount]", amount);
    const auto item = eResourceTypeHelpers::typeLongName(mResource);
    eStringHelpers::replaceAll(rFull, "[item]", item);
    t.trigger(*this, date, rFull);
}
