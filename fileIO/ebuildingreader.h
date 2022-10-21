#ifndef EBUILDINGREADER_H
#define EBUILDINGREADER_H

#include "buildings/ebuilding.h"
#include "fileIO/ereadstream.h"

namespace eBuildingReader {
    stdsptr<eBuilding> sRead(
            eGameBoard& board, const eBuildingType type,
            eReadStream& src);
};

#endif // EBUILDINGREADER_H
