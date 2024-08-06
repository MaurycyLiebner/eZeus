#include "esupplydemandchangeevent.h"

void eSupplyDemandChangeEvent::write(eWriteStream& dst) const {
    eBasicCityEvent::write(dst);
    dst << mType;
    dst << mBy;
}

void eSupplyDemandChangeEvent::read(eReadStream& src) {
    eBasicCityEvent::read(src);
    src >> mType;
    src >> mBy;
}
