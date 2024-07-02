#include "ecitybecomesevent.h"


#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "estringhelpers.h"
#include "elanguage.h"

eCityBecomesEvent::eCityBecomesEvent(const eGameEventBranch branch) :
    eGameEvent(eGameEventType::cityBecomes, branch) {}

void eCityBecomesEvent::trigger() {
    if(!mCity) return;
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fCity = mCity;
    switch(mType) {
    case eCityBecomesType::ally: {
        mCity->setRelationship(eForeignCityRelationship::ally);
        board->allow(eBuildingType::commemorative, 7);
        board->event(eEvent::cityBecomesAlly, ed);
    } break;
    case eCityBecomesType::rival: {
        mCity->setRelationship(eForeignCityRelationship::rival);
        board->event(eEvent::cityBecomesRival, ed);
    } break;
    case eCityBecomesType::vassal: {
        mCity->setRelationship(eForeignCityRelationship::vassal);
        board->event(eEvent::cityBecomesVassal, ed);
    } break;
    }
}

std::string eCityBecomesEvent::longName() const {
    auto text = eLanguage::text("city_becomes_long_name");
    std::string key;
    switch(mType) {
    case eCityBecomesType::ally: {
        key = "ally";
    } break;
    case eCityBecomesType::rival: {
        key = "rival";
    } break;
    case eCityBecomesType::vassal: {
        key = "vassal";
    } break;
    }

    const auto cname = mCity ? mCity->name() : eLanguage::text("city");
    eStringHelpers::replace(text, "%1", cname);
    eStringHelpers::replace(text, "%2", eLanguage::text(key));
    return text;
}

void eCityBecomesEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mType;
    dst.writeCity(mCity.get());
}

void eCityBecomesEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mType;
    src.readCity(worldBoard(), [this](const stdsptr<eWorldCity>& c) {
        mCity = c;
    });
}
