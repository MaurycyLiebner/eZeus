#include "ereceiverequestevent.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "emessages.h"
#include "engine/ecityrequest.h"

eReceiveRequestEvent::eReceiveRequestEvent(
        const eGameEventBranch branch,
        eGameBoard& board) :
    eGameEvent(eGameEventType::receiveRequest, branch, board) {
    const auto e1 = eLanguage::text("early");
    mEarlyTrigger = e::make_shared<eEventTrigger>(e1, board);
    const auto e2 = eLanguage::text("comply");
    mComplyTrigger = e::make_shared<eEventTrigger>(e2, board);
    const auto e3 = eLanguage::text("too_late");
    mTooLateTrigger = e::make_shared<eEventTrigger>(e3, board);
    const auto e4 = eLanguage::text("refuse");
    mRefuseTrigger = e::make_shared<eEventTrigger>(e4, board);

    addTrigger(mEarlyTrigger);
    addTrigger(mComplyTrigger);
    addTrigger(mTooLateTrigger);
    addTrigger(mRefuseTrigger);
}

eReceiveRequestEvent::~eReceiveRequestEvent() {
    auto& board = getBoard();
    board.removeCityRequest(this);
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
    auto& board = getBoard();
    eEventData ed;
    ed.fCity = mCity;
    ed.fResourceType = mResource;
    ed.fResourceCount = mCount;
    ed.fTime = 6;
    ed.fA0Key = "dispatch_now";
    ed.fA1Key = "postpone";
    ed.fA2Key = "refuse";

    const auto rel = mCity->relationship();

    if(mFinish) {
        auto& msgs = eMessages::instance;
        if(mPostpone > 1) {
            ed.fType = eMessageEventType::resourceGranted;
            eEvent event;
            eReceiveRequestMessages* rrmsgs = nullptr;
            if(rel == eWorldCityRelationship::rival) {
                event = eEvent::generalRequestRivalTooLate;
                rrmsgs = &msgs.fGeneralRequestRivalD;
            } else if(rel == eWorldCityRelationship::vassal ||
                      rel == eWorldCityRelationship::collony) {
                event = eEvent::generalRequestSubjectTooLate;
                rrmsgs = &msgs.fGeneralRequestSubjectP;
            } else if(rel == eWorldCityRelationship::mainCity) {
                event = eEvent::generalRequestParentTooLate;
                rrmsgs = &msgs.fGeneralRequestParentR;
            } else { // ally
                event = eEvent::generalRequestAllyTooLate;
                rrmsgs = &msgs.fGeneralRequestAllyS;
            }
            board.event(event, ed);
            mCity->incAttitude(-5);

            const auto& reason = rrmsgs->fTooLateReason;
            const auto me = mainEvent<eReceiveRequestEvent>();
            me->finished(*mTooLateTrigger, reason);
        } else {
            ed.fType = eMessageEventType::resourceGranted;
            eEvent event;
            eReceiveRequestMessages* rrmsgs = nullptr;
            if(rel == eWorldCityRelationship::rival) {
                event = eEvent::generalRequestRivalComply;
                rrmsgs = &msgs.fGeneralRequestRivalD;
            } else if(rel == eWorldCityRelationship::vassal ||
                      rel == eWorldCityRelationship::collony) {
                event = eEvent::generalRequestSubjectComply;
                rrmsgs = &msgs.fGeneralRequestSubjectP;
            } else if(rel == eWorldCityRelationship::mainCity) {
                event = eEvent::generalRequestParentComply;
                rrmsgs = &msgs.fGeneralRequestParentR;
            } else { // ally
                event = eEvent::generalRequestAllyComply;
                rrmsgs = &msgs.fGeneralRequestAllyS;
            }
            board.event(event, ed);
            mCity->incAttitude(10);

            const auto& reason = rrmsgs->fComplyReason;
            const auto me = mainEvent<eReceiveRequestEvent>();
            me->finished(*mComplyTrigger, reason);
        }
        return;
    }

    if(mPostpone > 3) {
        ed.fType = eMessageEventType::resourceGranted;
        eEvent event;
        eReceiveRequestMessages* rrmsgs = nullptr;
        auto& msgs = eMessages::instance;
        if(rel == eWorldCityRelationship::rival) {
            event = eEvent::generalRequestRivalRefuse;
            rrmsgs = &msgs.fGeneralRequestRivalD;
        } else if(rel == eWorldCityRelationship::vassal ||
                  rel == eWorldCityRelationship::collony) {
            event = eEvent::generalRequestSubjectRefuse;
            rrmsgs = &msgs.fGeneralRequestSubjectP;
        } else if(rel == eWorldCityRelationship::mainCity) {
            event = eEvent::generalRequestParentRefuse;
            rrmsgs = &msgs.fGeneralRequestParentR;
        } else { // ally
            event = eEvent::generalRequestAllyRefuse;
            rrmsgs = &msgs.fGeneralRequestAllyS;
        }
        board.event(event, ed);
        mCity->incAttitude(-15);

        auto& reason = rrmsgs->fRefuseReason;
        const auto me = mainEvent<eReceiveRequestEvent>();
        me->finished(*mRefuseTrigger, reason);
        return;
    }

    const int avCount = board.resourceCount(mResource);
    ed.fSpaceCount = avCount;

    ed.fType = eMessageEventType::requestTributeGranted;
    if(avCount >= mCount) {
        ed.fA0 = [this]() { // dispatch now
            dispatch();
        };
    }

    if(mPostpone < 3) {
        ed.fA1 = [this]() { // postpone
            auto& board = getBoard();
            const auto e = e::make_shared<eReceiveRequestEvent>(
                               eGameEventBranch::child, board);
            e->initialize(mPostpone + 1, mResource, mCount, mCity);
            const auto date = board.date() + gPostponeDays;
            e->initializeDate(date);
            addConsequence(e);
        };
    }

    ed.fA2 = [this]() { // refuse
        auto& board = getBoard();
        board.removeCityRequest(mainEvent<eReceiveRequestEvent>());
        const auto e = e::make_shared<eReceiveRequestEvent>(
                           eGameEventBranch::child, board);
        e->initialize(5, mResource, mCount, mCity);
        const auto date = board.date() + 31;
        e->initializeDate(date);
        addConsequence(e);
    };


    ed.fType = eMessageEventType::generalRequestGranted;
    if(mPostpone == 0) { // initial
        const auto request = cityRequest();
        board.addCityRequest(mainEvent<eReceiveRequestEvent>());
    }
    if(rel == eWorldCityRelationship::rival) {
        if(mPostpone == 0) { // initial
            board.event(eEvent::generalRequestRivalInitial, ed);
        } else if(mPostpone == 1) { // reminder
            board.event(eEvent::generalRequestRivalReminder, ed);
        } else if(mPostpone == 2) { // overdue
            board.event(eEvent::generalRequestRivalOverdue, ed);
        } else if(mPostpone == 3) { // warning
            board.event(eEvent::generalRequestRivalWarning, ed);
        }
    } else if(rel == eWorldCityRelationship::vassal ||
              rel == eWorldCityRelationship::collony) {
        if(mPostpone == 0) { // initial
            board.event(eEvent::generalRequestSubjectInitial, ed);
        } else if(mPostpone == 1) { // reminder
            board.event(eEvent::generalRequestSubjectReminder, ed);
        } else if(mPostpone == 2) { // overdue
            board.event(eEvent::generalRequestSubjectOverdue, ed);
        } else if(mPostpone == 3) { // warning
            board.event(eEvent::generalRequestSubjectWarning, ed);
        }
    } else if(rel == eWorldCityRelationship::mainCity) {
        if(mPostpone == 0) { // initial
            board.event(eEvent::generalRequestParentInitial, ed);
        } else if(mPostpone == 1) { // reminder
            board.event(eEvent::generalRequestParentReminder, ed);
        } else if(mPostpone == 2) { // overdue
            board.event(eEvent::generalRequestParentOverdue, ed);
        } else if(mPostpone == 3) { // warning
            board.event(eEvent::generalRequestParentWarning, ed);
        }
    } else { // ally
        if(mPostpone == 0) { // initial
            board.event(eEvent::generalRequestAllyInitial, ed);
        } else if(mPostpone == 1) { // reminder
            board.event(eEvent::generalRequestAllyReminder, ed);
        } else if(mPostpone == 2) { // overdue
            board.event(eEvent::generalRequestAllyOverdue, ed);
        } else if(mPostpone == 3) { // warning
            board.event(eEvent::generalRequestAllyWarning, ed);
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
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}

stdsptr<eGameEvent> eReceiveRequestEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eReceiveRequestEvent>(
                       branch(), getBoard());
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
    auto& board = getBoard();
    board.removeCityRequest(mainEvent<eReceiveRequestEvent>());
    board.takeResource(mResource, mCount);
    const auto e = e::make_shared<eReceiveRequestEvent>(*this);
    int postpone = mPostpone - 1;
    auto date = startDate();
    const auto currentDate = board.date();
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
    const auto& board = getBoard();
    const auto date = board.date();
    auto rFull = r.fFull;
    const auto amount = std::to_string(mCount);
    eStringHelpers::replaceAll(rFull, "[amount]", amount);
    const auto item = eResourceTypeHelpers::typeLongName(mResource);
    eStringHelpers::replaceAll(rFull, "[item]", item);
    t.trigger(*this, date, rFull);
}
