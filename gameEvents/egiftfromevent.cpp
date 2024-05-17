#include "egiftfromevent.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"

eGiftFromEvent::eGiftFromEvent(const eGameEventBranch branch,
                               eGameBoard& board) :
    eGameEvent(eGameEventType::giftFrom, branch, board) {}

void eGiftFromEvent::initialize(
        const bool postpone,
        const eResourceType res,
        const int count,
        const stdsptr<eWorldCity> &c) {
    mPostpone = postpone;
    mResource = res;
    mCount = count;
    mCity = c;
}

void eGiftFromEvent::trigger() {
    if(!mCity) return;
    auto& board = getBoard();
    const int space = board.spaceForResource(mResource);
    eEventData ed;
    ed.fCity = mCity;
    ed.fSpaceCount = space;
    ed.fResourceType = mResource;
    ed.fResourceCount = mCount;

    if(space == 0) {
        ed.fType = eMessageEventType::resourceGranted;
        if(mPostpone) {
            const auto e = e::make_shared<eGiftFromEvent>(
                        *this);
            e->initialize(false, mResource, mCount, mCity);
            const auto date = board.date() + 31;
            e->initializeDate(date);
            addConsequence(e);
        }
    } else {
        ed.fType = eMessageEventType::requestTributeGranted;
        if(space != 0) {
            ed.fA0 = [this]() { // accept
                auto& board = getBoard();
                const int a = board.addResource(mResource, mCount);
                eEventData ed;
                ed.fType = eMessageEventType::resourceGranted;
                ed.fCity = mCity;
                ed.fResourceType = mResource;
                ed.fResourceCount = a;
                if(mResource == eResourceType::drachmas) {
                    board.event(eEvent::giftCashAccepted, ed);
                } else {
                    if(a == mCount) return;
                    board.event(eEvent::giftAccepted, ed);
                }
            };
        }

        if(mPostpone) {
            ed.fA1 = [this]() { // postpone
                auto& board = getBoard();
                eEventData ed;
                ed.fType = eMessageEventType::resourceGranted;
                ed.fCity = mCity;
                ed.fResourceType = mResource;
                ed.fResourceCount = mCount;
                board.event(eEvent::giftPostponed, ed);

                const auto e = e::make_shared<eGiftFromEvent>(
                            *this);
                e->initialize(false, mResource, mCount, mCity);
                const auto date = board.date() + 31;
                e->initializeDate(date);
                addConsequence(e);
            };
        }

        ed.fA2 = [this]() { // decline
            auto& board = getBoard();
            eEventData ed;
            ed.fType = eMessageEventType::resourceGranted;
            ed.fCity = mCity;
            ed.fResourceType = mResource;
            ed.fResourceCount = mCount;
            board.event(eEvent::giftRefused, ed);
        };
    }
    if(!mPostpone) {
        if(space == 0) {
            board.event(eEvent::giftForfeited, ed);
        } else if(space >= mCount) {
            board.event(eEvent::giftGranted, ed);
        } else {
            board.event(eEvent::giftLastChance, ed);
        }
    } else if(space == 0) {
        board.event(eEvent::giftInsufficientSpace, ed);
    } else if(space >= mCount) {
        board.event(eEvent::giftGranted, ed);
    } else {
        board.event(eEvent::giftPartialSpace, ed);
    }
}

std::string eGiftFromEvent::longName() const {
    auto tmpl = eLanguage::text("gift_of_from");
    const auto resName = eResourceTypeHelpers::typeName(mResource);
    const auto cStr = std::to_string(mCount);
    const auto none = eLanguage::text("none");
    const auto ctstr = mCity ? mCity->name() : none;
    eStringHelpers::replace(tmpl, "%1", cStr + " " + resName);
    eStringHelpers::replace(tmpl, "%2", ctstr);
    return tmpl;
}

void eGiftFromEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mPostpone;
    dst << mResource;
    dst << mCount;
    dst.writeCity(mCity.get());
}

void eGiftFromEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mPostpone;
    src >> mResource;
    src >> mCount;
    src.readCity(&getBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}

stdsptr<eGameEvent> eGiftFromEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eGiftFromEvent>(branch(), getBoard());
    c->setReason(reason);
    c->initialize(mPostpone, mResource, mCount, mCity);
    return c;
}

void eGiftFromEvent::setCity(const stdsptr<eWorldCity>& c) {
    mCity = c;
}

void eGiftFromEvent::setResourceType(const eResourceType type) {
    mResource = type;
}

void eGiftFromEvent::setResourceCount(const int c) {
    mCount = c;
}
