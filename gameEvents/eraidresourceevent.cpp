#include "eraidresourceevent.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "estringhelpers.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"

eRaidResourceEvent::eRaidResourceEvent(const eGameEventBranch branch) :
    eResourceGrantedEventBase(
        eEvent::raidCashAccepted,
        eEvent::raidAccepted,
        eEvent::raidPostponed,
        eEvent::raidRefused,
        eEvent::raidForfeited,
        eEvent::raidGranted,
        eEvent::raidLastChance,
        eEvent::raidInsufficientSpace,
        eEvent::raidPartialSpace,
        eGameEventType::raidResourceReceive, branch) {}

std::string eRaidResourceEvent::longName() const {
    return eLanguage::text("raid_resource_long_name");
}

stdsptr<eGameEvent> eRaidResourceEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eRaidResourceEvent>(branch());
    c->setGameBoard(gameBoard());
    c->setWorldBoard(worldBoard());
    c->setReason(reason);
    c->initialize(mPostpone, mResource, mCount, mCity);
    return c;
}
