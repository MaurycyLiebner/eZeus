#include "emakerequestevent.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "engine/egifthelpers.h"

eMakeRequestEvent::eMakeRequestEvent(
        eGameBoard& board) :
    eGameEvent(eGameEventType::makeRequest, board) {}

void eMakeRequestEvent::initialize(
        const bool postpone,
        const eResourceType res,
        const stdsptr<eWorldCity> &c) {
    mPostpone = postpone;
    mResource = res;
    mCity = c;
}

void eMakeRequestEvent::trigger() {
    if(!mCity) return;
    auto& board = getBoard();
    const int count = 2*eGiftHelpers::giftCount(mResource);

    const int space = board.spaceForResource(mResource);
    eEventData ed;
    ed.fCity = mCity;
    ed.fSpaceCount = space;
    ed.fResourceType = mResource;
    ed.fResourceCount = count;

    if(space == 0) {
        ed.fType = eMessageEventType::resourceGranted;
        if(mPostpone) {
            const auto e = e::make_shared<eMakeRequestEvent>(
                        *this);
            e->initialize(false, mResource, mCity);
            const auto date = board.date() + 31;
            e->initializeDate(date);
            addConsequence(e);
        }
    } else {
        ed.fType = eMessageEventType::requestTributeGranted;
        if(space != 0) {
            ed.fA0 = [this, count]() { // accept
                auto& board = getBoard();
                const int a = board.addResource(mResource, count);
                if(a == count) return;
                eEventData ed;
                ed.fType = eMessageEventType::resourceGranted;
                ed.fCity = mCity;
                ed.fResourceType = mResource;
                ed.fResourceCount = a;
                board.event(eEvent::requestAccepted, ed);
            };
        }

        if(mPostpone) {
            ed.fA1 = [this, count]() { // postpone
                auto& board = getBoard();
                eEventData ed;
                ed.fType = eMessageEventType::resourceGranted;
                ed.fCity = mCity;
                ed.fResourceType = mResource;
                ed.fResourceCount = count;
                board.event(eEvent::requestPostponed, ed);

                const auto e = e::make_shared<eMakeRequestEvent>(
                            *this);
                e->initialize(false, mResource, mCity);
                const auto date = board.date() + 31;
                e->initializeDate(date);
                addConsequence(e);
            };
        }

        ed.fA2 = [this, count]() { // decline
            auto& board = getBoard();
            eEventData ed;
            ed.fType = eMessageEventType::resourceGranted;
            ed.fCity = mCity;
            ed.fResourceType = mResource;
            ed.fResourceCount = count;
            board.event(eEvent::requestRefused, ed);
        };
    }
    if(!mPostpone) {
        if(space == 0) {
            board.event(eEvent::requestForfeited, ed);
        } else if(space >= count) {
            board.event(eEvent::requestGranted, ed);
        } else {
            board.event(eEvent::requestLastChance, ed);
        }
    } else if(space == 0) {
        board.event(eEvent::requestInsufficientSpace, ed);
    } else if(space >= count) {
        board.event(eEvent::requestGranted, ed);
    } else {
        board.event(eEvent::requestPartialSpace, ed);
    }
}

std::string eMakeRequestEvent::longName() const {
    auto tmpl = eLanguage::text("make_request");
    const auto resName = eResourceTypeHelpers::typeName(mResource);
    eStringHelpers::replace(tmpl, "%1", resName);
    const auto none = eLanguage::text("none");
    const auto ctstr = mCity ? mCity->name() : none;
    eStringHelpers::replace(tmpl, "%2", ctstr);
    return tmpl;
}

void eMakeRequestEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mPostpone;
    dst << mResource;
    dst.writeCity(mCity.get());
}

void eMakeRequestEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mPostpone;
    src >> mResource;
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}

stdsptr<eGameEvent> eMakeRequestEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eMakeRequestEvent>(getBoard());
    c->initialize(mPostpone, mResource, mCity);
    c->setReason(reason);
    return c;
}


void eMakeRequestEvent::setCity(const stdsptr<eWorldCity>& c) {
    mCity = c;
}

void eMakeRequestEvent::setResourceType(const eResourceType type) {
    mResource = type;
}
