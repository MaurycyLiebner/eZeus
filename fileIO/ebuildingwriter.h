#ifndef EBUILDINGWRITER_H
#define EBUILDINGWRITER_H

#include "buildings/ebuilding.h"
#include "fileIO/ewritestream.h"

namespace eBuildingWriter {
    void sWrite(const eBuilding* const b,
                eWriteStream& dst);
};

#endif // EBUILDINGWRITER_H
