#ifndef EBUILDINGRENDERERREADER_H
#define EBUILDINGRENDERERREADER_H

#include "buildings/ebuildingrenderer.h"
#include "fileIO/ereadstream.h"

namespace eBuildingRendererReader {
    stdsptr<eBuildingRenderer> sRead(const stdsptr<eBuilding>& b,
                                     const eBuildingRendererType type,
                                     eReadStream& src);
};

#endif // EBUILDINGRENDERERREADER_H
