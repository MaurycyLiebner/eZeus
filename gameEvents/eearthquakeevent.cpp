#include "eearthquakeevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"

eEarthquakeEvent::eEarthquakeEvent(const eGameEventBranch branch) :
    eGameEvent(eGameEventType::earthquake, branch) {}

void eEarthquakeEvent::trigger() {
    const auto board = gameBoard();
    if(!board) return;
    const auto startTile = board->disasterTile(mDisasterPoint);
    if(!startTile) return;
    eEventData ed;
    ed.fGod = mGod;
    ed.fTile = startTile;
    board->earthquake(startTile, mSize);
    board->event(eEvent::earthquake, ed);
}

std::string eEarthquakeEvent::longName() const {
    return eLanguage::text("earthquake_long_name");
}

void eEarthquakeEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mDisasterPoint;
    dst << mGod;
    dst << mSize;
}

void eEarthquakeEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mDisasterPoint;
    src >> mGod;
    src >> mSize;
}
