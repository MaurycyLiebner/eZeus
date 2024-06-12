#include "eresourcegrantedeventbase.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"

eResourceGrantedEventBase::eResourceGrantedEventBase(
        const eEvent giftCashAccepted,
        const eEvent giftAccepted,
        const eEvent giftPostponed,
        const eEvent giftRefused,
        const eEvent giftForfeited,
        const eEvent giftGranted,
        const eEvent giftLastChance,
        const eEvent giftInsufficientSpace,
        const eEvent giftPartialSpace,
        const eGameEventType type,
        const eGameEventBranch branch) :
    eGameEvent(type, branch),
    mGiftCashAccepted(giftCashAccepted),
    mGiftAccepted(giftAccepted),
    mGiftPostponed(giftPostponed),
    mGiftRefused(giftRefused),
    mGiftForfeited(giftForfeited),
    mGiftGranted(giftGranted),
    mGiftLastChance(giftLastChance),
    mGiftInsufficientSpace(giftInsufficientSpace),
    mGiftPartialSpace(giftPartialSpace) {}

void eResourceGrantedEventBase::initialize(
        const bool postpone,
        const eResourceType res,
        const int count,
        const stdsptr<eWorldCity> &c) {
    mPostpone = postpone;
    mResource = res;
    mCount = count;
    mCity = c;
}

void eResourceGrantedEventBase::trigger() {
    if(!mCity) return;
    const auto board = gameBoard();
    if(!board) return;
    const int space = board->spaceForResource(mResource);
    eEventData ed;
    ed.fCity = mCity;
    ed.fSpaceCount = space;
    ed.fResourceType = mResource;
    ed.fResourceCount = mCount;

    if(space == 0) {
        ed.fType = eMessageEventType::resourceGranted;
        if(mPostpone) {
            const auto branch = eGameEventBranch::child;
            const auto e = eGameEvent::sCreate(type(), branch, board);
            using eRGEB = eResourceGrantedEventBase;
            const auto ee = static_cast<eRGEB*>(e.get());
            ee->initialize(false, mResource, mCount, mCity);
            const auto date = board->date() + 31;
            e->initializeDate(date);
            addConsequence(e);
        }
    } else {
        ed.fType = eMessageEventType::requestTributeGranted;
        if(space != 0) {
            ed.fA0 = [this, board]() { // accept
                const int a = board->addResource(mResource, mCount);
                eEventData ed;
                ed.fType = eMessageEventType::resourceGranted;
                ed.fCity = mCity;
                ed.fResourceType = mResource;
                ed.fResourceCount = a;
                if(mResource == eResourceType::drachmas) {
                    board->event(mGiftCashAccepted, ed);
                } else {
                    if(a == mCount) return;
                    board->event(mGiftAccepted, ed);
                }
            };
        }

        if(mPostpone) {
            ed.fA1 = [this, board]() { // postpone
                eEventData ed;
                ed.fType = eMessageEventType::resourceGranted;
                ed.fCity = mCity;
                ed.fResourceType = mResource;
                ed.fResourceCount = mCount;
                board->event(mGiftPostponed, ed);

                const auto branch = eGameEventBranch::child;
                const auto e = eGameEvent::sCreate(type(), branch, board);
                using eRGEB = eResourceGrantedEventBase;
                const auto ee = static_cast<eRGEB*>(e.get());
                ee->initialize(false, mResource, mCount, mCity);
                const auto date = board->date() + 31;
                e->initializeDate(date);
                addConsequence(e);
            };
        }

        ed.fA2 = [this, board]() { // decline
            eEventData ed;
            ed.fType = eMessageEventType::resourceGranted;
            ed.fCity = mCity;
            ed.fResourceType = mResource;
            ed.fResourceCount = mCount;
            board->event(mGiftRefused, ed);
        };
    }
    if(!mPostpone) {
        if(space == 0) {
            board->event(mGiftForfeited, ed);
        } else if(space >= mCount) {
            board->event(mGiftGranted, ed);
        } else {
            board->event(mGiftLastChance, ed);
        }
    } else if(space == 0) {
        board->event(mGiftInsufficientSpace, ed);
    } else if(space >= mCount) {
        board->event(mGiftGranted, ed);
    } else {
        board->event(mGiftPartialSpace, ed);
    }
}

void eResourceGrantedEventBase::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mPostpone;
    dst << mResource;
    dst << mCount;
    dst.writeCity(mCity.get());
}

void eResourceGrantedEventBase::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mPostpone;
    src >> mResource;
    src >> mCount;
    src.readCity(worldBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}

void eResourceGrantedEventBase::setCity(const stdsptr<eWorldCity>& c) {
    mCity = c;
}

void eResourceGrantedEventBase::setResourceType(const eResourceType type) {
    mResource = type;
}

void eResourceGrantedEventBase::setResourceCount(const int c) {
    mCount = c;
}
